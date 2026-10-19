"""Synthetic mapping/dispatch checks; no original ROM or modules are read."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_backend
from project import GateError, REVISION, sha256


def layout_fixture():
    return {
        'modules': [{'module': 'arm9', 'load_address': 0x02000000,
                     'rom_offset': 0x4000, 'stored_size': 32, 'sha256': sha256(b'A' * 32)}],
        'overlays': [{'module': 'arm9/ov000', 'address': 0x02000000,
                      'rom_offset': 0x5000, 'stored_size': 32, 'ram_size': 32,
                      'bss_size': 16, 'ctor_start': 0x02000018, 'ctor_end': 0x02000020,
                      'file_id': 0, 'compressed': False, 'flags': 0}],
        'filesystem': [{'id': 0, 'rom_offset': 0x5000, 'size': 32, 'sha256': sha256(b'O' * 32)}],
        'chunks': [{'name': 'arm9', 'file': 'arm9.bin', 'start': 0x4000,
                    'end': 0x4020, 'sha256': sha256(b'A' * 32)},
                   {'name': 'file-0000', 'file': 'overlay.bin', 'start': 0x5000,
                    'end': 0x5020, 'sha256': sha256(b'O' * 32)}],
    }


class OverlayMappingTests(unittest.TestCase):
    def test_overlay_uses_fat_chunk_and_stored_extent_not_bss(self):
        layout = layout_fixture()
        module, chunk = link_backend.module_input(layout, 'arm9/ov000')
        self.assertEqual(chunk['name'], 'file-0000')
        self.assertEqual(module['load_address'], 0x02000000)
        self.assertEqual(module['stored_size'], 32)
        self.assertEqual(module['sha256'], sha256(b'O' * 32))
        self.assertEqual(layout, layout_fixture())

    def test_unreviewed_modules_rejected(self):
        for name in ('arm7', 'arm9/ov001', 'arm9/ov002', 'ov000'):
            with self.subTest(name=name), self.assertRaisesRegex(GateError, 'unreviewed'):
                link_backend.module_input(layout_fixture(), name)

    def test_compression_flags_and_expansion_rejected(self):
        for key, value in [('compressed', True), ('flags', 0x1000000),
                           ('flags', 1), ('ram_size', 48)]:
            layout = layout_fixture()
            layout['overlays'][0][key] = value
            with self.subTest(key=key, value=value), self.assertRaisesRegex(GateError, 'uncompressed'):
                link_backend.module_input(layout, 'arm9/ov000')

    def test_fat_chunk_mapping_and_hashes_must_agree(self):
        for table, key, value in [('filesystem', 'rom_offset', 0x6000),
                                  ('filesystem', 'size', 48),
                                  ('chunks', 'start', 0x5004),
                                  ('chunks', 'end', 0x5024),
                                  ('chunks', 'sha256', '0' * 64)]:
            layout = layout_fixture()
            row = layout[table][-1]
            row[key] = value
            with self.subTest(table=table, key=key), self.assertRaisesRegex(GateError, 'mapping mismatch'):
                link_backend.module_input(layout, 'arm9/ov000')

    def test_missing_or_duplicate_mapping_fails_closed(self):
        for table in ('overlays', 'filesystem', 'chunks'):
            for duplicate in (False, True):
                layout = layout_fixture()
                if duplicate:
                    layout[table].append(copy.deepcopy(layout[table][-1]))
                else:
                    layout[table].pop()
                with self.subTest(table=table, duplicate=duplicate), self.assertRaisesRegex(GateError, 'mapping'):
                    link_backend.module_input(layout, 'arm9/ov000')

    def test_constructor_extent_must_remain_in_stored_image(self):
        for key, value in [('ctor_start', 0x01fffffc), ('ctor_end', 0x02000024),
                           ('ctor_start', 0x02000024)]:
            layout = layout_fixture()
            layout['overlays'][0][key] = value
            with self.subTest(key=key), self.assertRaisesRegex(GateError, 'constructors'):
                link_backend.module_input(layout, 'arm9/ov000')

    def dispatch_fixture(self, root):
        layout = layout_fixture()
        config = root / 'config' / REVISION
        chunks = root / 'extract' / REVISION / 'chunks'
        source = root / 'src' / 'auto'
        config.mkdir(parents=True)
        chunks.mkdir(parents=True)
        source.mkdir(parents=True)
        (config / 'rom-layout.json').write_text(json.dumps(layout))
        profile = {'symbol_values': {}}
        for name in ('compiler', 'linker'):
            (config / (name + '.json')).write_text(json.dumps(profile))
        (chunks / 'arm9.bin').write_bytes(b'A' * 32)
        (chunks / 'overlay.bin').write_bytes(b'O' * 32)
        functions, entries = [], []
        for index, (module, offset) in enumerate([('arm9', 0x4000), ('arm9/ov000', 0x5000)]):
            raw = f'int fixture{index}(int x) {{ return x; }}\n'.encode()
            path = source / f'fixture{index}.c'
            path.write_bytes(raw)
            fn = {'id': f'fixture{index}', 'module': module, 'address': 0x02000000,
                  'mode': 'arm', 'size': 8, 'code_size': 8, 'rom_offset': offset}
            functions.append(fn)
            entries.append({'id': fn['id'], 'source': str(path.relative_to(root)),
                            'source_sha256': sha256(raw), 'profile': f'config/{REVISION}/compiler.json',
                            'profile_sha256': sha256((config / 'compiler.json').read_bytes()),
                            'symbol': f'fixture{index}'})
        plan = {'functions': entries, 'linker': f'config/{REVISION}/linker.json',
                'linker_sha256': sha256((config / 'linker.json').read_bytes())}
        return plan, {'functions': functions}

    def test_dispatches_separate_module_vmas_to_exact_chunk_names(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            plan, universe = self.dispatch_fixture(root)
            with (mock.patch.object(link_backend, 'validate_declaration', return_value=(plan, universe)),
                  mock.patch.object(link_backend, 'compile_bytes', return_value=(b'fixture-object', '')),
                  mock.patch.object(link_backend, 'link_module', side_effect=lambda original, *args: original) as linker):
                images = link_backend.linked_modules(root)
            self.assertEqual(images, {'arm9': b'A' * 32, 'file-0000': b'O' * 32})
            self.assertEqual(linker.call_count, 2)
            self.assertEqual([c.args[2][0][0]['module'] for c in linker.call_args_list],
                             ['arm9', 'arm9/ov000'])

    def test_wrong_overlay_rom_mapping_and_constructor_overlap_rejected(self):
        for key, value, message in [('rom_offset', 0x5004, 'ROM/VMA mapping'),
                                     ('address', 0x02000018, 'constructor')]:
            with tempfile.TemporaryDirectory() as td:
                root = Path(td)
                plan, universe = self.dispatch_fixture(root)
                fn = universe['functions'][1]
                fn[key] = value
                if key == 'address':
                    fn['rom_offset'] += 24
                with (mock.patch.object(link_backend, 'validate_declaration', return_value=(plan, universe)),
                      mock.patch.object(link_backend, 'compile_bytes', return_value=(b'fixture-object', '')),
                      mock.patch.object(link_backend, 'link_module', side_effect=lambda original, *args: original),
                      self.assertRaisesRegex(GateError, message)):
                    link_backend.linked_modules(root)


if __name__ == '__main__':
    unittest.main()
