"""Synthetic boundary fixtures are test inputs, never reconstructed function source."""
import copy
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from project import (GateError, ROOT, REVISION, original, pipeline_lock, read_json,
                     validate_universe, isolation)
from probe_compiler import compare, target_bytes
from wip_support import compile_function
from workflow import format_paths


class Gates(unittest.TestCase):
    def test_format_change_stops_gate_and_is_idempotent(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            p = root / 'README.md'
            p.write_text('review me  \n\n\n')
            with mock.patch('workflow.ROOT', root):
                with self.assertRaisesRegex(GateError, 'formatting changed'):
                    format_paths(['README.md'])
                self.assertEqual(p.read_text(), 'review me\n')
                format_paths(['README.md'])

    def test_corrupt_component_rejected_before_output(self):
        import rom
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            chunks = root / 'extract' / REVISION / 'chunks'
            chunks.mkdir(parents=True)
            (chunks / 'fixture.bin').write_bytes(b'changed')
            plan = {'chunks': [{'file': 'fixture.bin', 'name': 'fixture', 'start': 0,
                                'end': 7, 'sha256': '0' * 64}]}
            with (mock.patch('rom.isolation'), mock.patch('rom.read_json', return_value=plan),
                  mock.patch('link_backend.linked_modules', return_value={})):
                with self.assertRaisesRegex(GateError, 'changed target component'):
                    rom.build(root)
            self.assertFalse((root / 'build' / REVISION / 'pvz.nds').exists())

    def test_wrong_rom_identity(self):
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / "wrong.nds"
            p.write_bytes(b"wrong ROM")
            with self.assertRaisesRegex(GateError, "immutable"):
                original(p)

    def test_wrong_target_metadata(self):
        universe = read_json(ROOT / "config" / REVISION / "functions-v1.json")
        fn = copy.deepcopy(universe['functions'][2])
        fn['address'] += 4
        with mock.patch('probe_compiler.original', return_value=b''):
            with self.assertRaisesRegex(GateError, 'wrong/unbounded target'):
                target_bytes('unused', fn)

    def test_size_mismatch_never_zero_diff(self):
        result = compare(bytes.fromhex('0000a0e31eff2fe1'), b'\x00', 'arm', 0, 8)
        self.assertEqual(result['tier'], 'X')
        self.assertIsNone(result['instruction_differences'])
        self.assertGreater(result['resolved_byte_differences'], 0)

    def test_register_sensitive_comparison(self):
        left = bytes.fromhex('0000a0e11eff2fe1')  # synthetic mov r0,r0; bx lr
        right = bytes.fromhex('0100a0e11eff2fe1')  # synthetic mov r0,r1; bx lr
        result = compare(left, right, 'arm', 0, 8)
        self.assertEqual(result['instruction_differences'], 1)
        self.assertEqual(result['tier'], 'N')
        self.assertFalse(result['registers_normalized'])
        self.assertEqual(result['masked_fields'], [])

    def test_thumb_register_sensitive(self):
        result = compare(bytes.fromhex('00467047'), bytes.fromhex('08467047'), 'thumb', 0, 4)
        self.assertEqual(result['instruction_differences'], 1)
        self.assertEqual(result['tier'], 'N')

    def test_duplicate_and_overlap_credit(self):
        f = {'module': 'arm9', 'address': 0x100, 'mode': 'arm', 'size': 8, 'code_size': 8}
        with self.assertRaisesRegex(GateError, 'duplicate'):
            validate_universe({'functions': [f, f]})
        g = dict(f, address=0x104)
        with self.assertRaisesRegex(GateError, 'overlapping'):
            validate_universe({'functions': [f, g]})
        g = dict(f, module='arm9/ov000')
        self.assertEqual(len(validate_universe({'functions': [f, g]})), 2)

    def test_semantic_isolation(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'semantic').mkdir()
            with self.assertRaisesRegex(GateError, 'must not exist'):
                isolation(root)
            (root / 'semantic').rmdir()
            (root / 'src').mkdir()
            (root / 'src/unsafe.c').write_text('#include "../../../semantic/x.h"\n')
            with self.assertRaisesRegex(GateError, 'reference'):
                isolation(root)

    def test_concurrent_strict_writers(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            subprocess.run(['git', 'init', '-q', '-b', 'decomp/strict', str(root)], check=True)
            with pipeline_lock(root):
                script = ('import sys; from pathlib import Path; '
                          f'sys.path.insert(0,{str(ROOT / "tools")!r}); '
                          'from project import pipeline_lock; '
                          f'ctx=pipeline_lock(Path({td!r})); ctx.__enter__()')
                result = subprocess.run([sys.executable, '-B', '-c', script], capture_output=True, text=True)
                self.assertNotEqual(result.returncode, 0)
                self.assertIn('another strict writer', result.stderr)

    def test_wrong_track_rejected(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            subprocess.run(['git', 'init', '-q', '-b', 'wip/semantic', str(root)], check=True)
            with self.assertRaisesRegex(GateError, 'Track-A'):
                with pipeline_lock(root):
                    self.fail('wrong branch entered strict pipeline')

    def compile_case(self, source, symbols=None):
        profile = read_json(ROOT / 'docs/profiles/clang23-arm946-o2.json')
        if symbols is not None:
            profile['symbol_values'] = symbols
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'source.c'
            path.write_text(source)
            return compile_function(path, profile)

    def test_compiler_failure_is_error(self):
        with self.assertRaisesRegex(GateError, 'compiler failure'):
            self.compile_case('unsigned broken( {\n')

    def test_unresolved_relocation_is_error(self):
        with self.assertRaisesRegex(GateError, 'unresolved relocation'):
            self.compile_case('extern unsigned external; unsigned *probe(void) { return &external; }\n')

    def test_resolved_abs32(self):
        data, _ = self.compile_case('extern unsigned external; unsigned *probe(void) { return &external; }\n',
                                    {'external': 0x10001000})
        self.assertIn((0x10001000).to_bytes(4, 'little'), data)

    def test_unsupported_call_relocation_is_error(self):
        with self.assertRaisesRegex(GateError, 'unsupported relocation'):
            self.compile_case('extern unsigned other(unsigned); unsigned probe(unsigned x) { return other(x) + 1; }\n')


if __name__ == '__main__':
    unittest.main()
