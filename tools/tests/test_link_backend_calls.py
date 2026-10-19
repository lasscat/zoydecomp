"""Synthetic-only call-aware linker regressions; no ROM or DS function IDs."""
from __future__ import annotations

from io import BytesIO
from pathlib import Path
import json
import subprocess
import sys
import tempfile
import unittest

STRICT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(STRICT / 'tools'))

import link_backend
from project import GateError, REVISION, read_json, sha256
from wip_support import compile_object

PROFILE = read_json(STRICT / 'docs/profiles/clang23-arm946-o2.json')
MWCC_PROFILE_PATH = STRICT / 'config/BWBE-r0/mwcc20-arm946-o2-interwork.json'
BASE = 0x02000000


def parse(obj):
    from elftools.elf.elffile import ELFFile
    return ELFFile(BytesIO(obj))


def compile_c(source, profile=PROFILE):
    with tempfile.TemporaryDirectory(prefix='pvz-call-c-') as td:
        src = Path(td) / 'unit.c'
        src.write_text(source, encoding='ascii')
        return compile_object(src, profile)[0]


def text_bytes(obj):
    return parse(obj).get_section_by_name('.text').data()


def rel_records(obj):
    from elftools.elf.relocation import RelocationSection
    elf = parse(obj)
    rows = []
    for sec in elf.iter_sections():
        if isinstance(sec, RelocationSection):
            symtab = elf.get_section(sec['sh_link'])
            rows.extend((sec, rel, symtab.get_symbol(rel['r_info_sym']).name)
                        for rel in sec.iter_relocations())
    return rows


def mutate_relocation(obj, *, kind=None, offset=None, rela=False):
    """Hostile synthetic ELF fixtures only; never reconstructed game objects."""
    from elftools.elf.relocation import RelocationSection
    raw = bytearray(obj)
    elf = parse(obj)
    section_index, section = next((i, s) for i, s in enumerate(elf.iter_sections())
                                 if isinstance(s, RelocationSection)
                                 and elf.get_section(s['sh_info']).name == '.text')
    rel = next(section.iter_relocations())
    shoff = elf['e_shoff'] + section_index * 40
    roff = section['sh_offset']
    info = rel['r_info']
    if offset is not None:
        raw[roff:roff + 4] = int(offset & 0xffffffff).to_bytes(4, 'little')
    if kind is not None:
        info = (info & 0xffffff00) | kind
    raw[roff + 4:roff + 8] = info.to_bytes(4, 'little')
    if rela:
        appended = len(raw)
        raw.extend(raw[roff:roff + 8])
        raw.extend((0).to_bytes(4, 'little'))
        raw[shoff + 4:shoff + 8] = (4).to_bytes(4, 'little')
        raw[shoff + 16:shoff + 20] = appended.to_bytes(4, 'little')
        raw[shoff + 20:shoff + 24] = (12).to_bytes(4, 'little')
        raw[shoff + 36:shoff + 40] = (12).to_bytes(4, 'little')
    return bytes(raw)


def mutate_text_word(obj, offset, word):
    raw = bytearray(obj)
    sec = parse(obj).get_section_by_name('.text')
    start = sec['sh_offset'] + offset
    raw[start:start + 4] = word.to_bytes(4, 'little')
    return bytes(raw)


def mutate_call_symbol(obj, field, value):
    """Alter only a symbol-table field in an adversarial synthetic fixture."""
    elf = parse(obj)
    sec, rel, name = next(row for row in rel_records(obj)
                          if elf.get_section(row[0]['sh_info']).name == '.text')
    table = elf.get_section(sec['sh_link'])
    start = table['sh_offset'] + rel['r_info_sym'] * table['sh_entsize']
    off, size = {'value': (4, 4), 'size': (8, 4), 'info': (12, 1),
                 'other': (13, 1), 'shndx': (14, 2)}[field]
    raw = bytearray(obj)
    raw[start + off:start + off + size] = value.to_bytes(size, 'little')
    return bytes(raw)


def oracle_cluster(objects, records, linker):
    """Independently prelink natural C objects as the synthetic oracle."""
    addresses = [f'.fixture{i} 0x{fn["address"]:x} : {{ KEEP(obj{i}.o(.text)) }}'
                 for i, fn in enumerate(records)]
    script = ('OUTPUT_FORMAT(elf32-littlearm)\nOUTPUT_ARCH(arm)\nSECTIONS {\n'
              + '\n'.join(addresses)
              + '\n/DISCARD/ : { *(.ARM.exidx) *(.ARM.attributes) *(.comment) *(.note*) }\n}\n')
    with tempfile.TemporaryDirectory(prefix='pvz-call-oracle-') as td:
        work = Path(td)
        for i, obj in enumerate(objects):
            (work / f'obj{i}.o').write_bytes(obj)
        (work / 'oracle.ld').write_text(script)
        cmd = [linker['executable'], '--no-undefined', '-T', 'oracle.ld', '-o', 'oracle.elf',
               *[f'obj{i}.o' for i in range(len(objects))]]
        run = subprocess.run(cmd, cwd=work, capture_output=True, text=True, timeout=30)
        if run.returncode:
            raise AssertionError('synthetic LLD oracle failed: ' + run.stderr)
        elf = parse((work / 'oracle.elf').read_bytes())
        payloads = [elf.get_section_by_name(f'.fixture{i}').data() for i in range(4)]
        return b''.join(payloads), payloads


class CallClusterTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.linker_path = Path('/usr/bin/ld.lld')
        cls.linker = {'executable': str(cls.linker_path),
                      'executable_sha256': sha256(cls.linker_path.read_bytes()),
                      'version': subprocess.check_output([str(cls.linker_path), '--version'],
                                                         text=True).strip()}
        cls.sources = (
            'extern int beta(int); int alpha(int x) { return beta(x) + 3; }\n',
            'extern int gamma(int); int beta(int x) { return gamma(x) + 5; }\n',
            'extern int delta(int); int gamma(int x) { return delta(x) + 7; }\n',
            'int delta(int x) { return x * 2 + 1; }\n',
        )
        cls.objects = tuple(compile_c(src) for src in cls.sources)
        cls.sizes = tuple(len(text_bytes(obj)) for obj in cls.objects)
        cursor, cls.functions = BASE, []
        for name, size in zip(('alpha', 'beta', 'gamma', 'delta'), cls.sizes):
            cls.functions.append({'id': name, 'module': 'synthetic', 'mode': 'arm',
                                  'address': cursor, 'size': size, 'code_size': size})
            cursor += size
        cls.original, payloads = oracle_cluster(cls.objects, cls.functions, cls.linker)
        for fn, payload in zip(cls.functions, payloads):
            fn['target_sha256'] = sha256(payload)
        cls.blocks = [(fn, obj, fn['id']) for fn, obj in zip(cls.functions, cls.objects)]
        cls.edges = {'alpha': ['beta'], 'beta': ['gamma'], 'gamma': ['delta'], 'delta': []}

    def link(self, *, original=None, blocks=None, edges=None):
        with tempfile.TemporaryDirectory(prefix='pvz-call-link-') as td:
            return link_backend.link_module(self.original if original is None else original, BASE,
                    self.blocks if blocks is None else blocks, self.linker,
                    Path(td) / 'artifacts', self.edges if edges is None else edges)

    def test_four_natural_c_objects_resolve_and_match_prelinked_oracle(self):
        self.assertEqual([r[1]['r_info_type'] for r in rel_records(self.objects[0])
                          if parse(self.objects[0]).get_section(r[0]['sh_info']).name == '.text'], [28])
        self.assertEqual(self.link(), self.original)

    def test_synthetic_sht_rel_pc24_bl_resolves_without_patching(self):
        blocks = [(fn, mutate_relocation(obj, kind=1) if fn['id'] != 'delta' else obj, symbol)
                  for fn, obj, symbol in self.blocks]
        self.assertEqual(self.link(blocks=blocks), self.original)

    def test_call_cluster_preserves_opaque_prefix_and_tail(self):
        prefix, tail = b'opaque-prefix!!!', b'opaque-tail!'
        self.assertEqual(len(prefix) % 4, 0)
        blocks = [(dict(fn, address=fn['address'] + len(prefix)), obj, symbol)
                  for fn, obj, symbol in self.blocks]
        original = prefix + self.original + tail
        self.assertEqual(self.link(original=original, blocks=blocks), original)

    def test_clang_calls_can_target_an_optional_mwcc_leaf(self):
        profile = read_json(MWCC_PROFILE_PATH)
        if not (STRICT / profile['executable']).is_file():
            self.skipTest('optional reviewed MWCC executable is not installed')
        objects = [*self.objects[:3], compile_c(self.sources[3], profile)]
        functions = [dict(fn, size=len(text_bytes(obj)), code_size=len(text_bytes(obj)))
                     for fn, obj in zip(self.functions, objects)]
        original, payloads = oracle_cluster(objects, functions, self.linker)
        for fn, payload in zip(functions, payloads):
            fn['target_sha256'] = sha256(payload)
        blocks = [(fn, obj, fn['id']) for fn, obj in zip(functions, objects)]
        self.assertEqual(self.link(original=original, blocks=blocks), original)

    def test_unconfigured_calls_rejected(self):
        with self.assertRaisesRegex(GateError, 'unresolved/text relocation'):
            link_backend.inspect_object(self.objects[0], self.functions[0], 'alpha', {})
        with self.assertRaisesRegex(GateError, 'unresolved/text relocation'):
            self.link(edges={**self.edges, 'alpha': []})

    def test_tail_b_blx_abs32_rela_and_nonstandard_addend_rejected(self):
        obj = self.objects[0]
        mutants = [mutate_relocation(obj, kind=29), mutate_relocation(obj, kind=2),
                   mutate_relocation(obj, rela=True), mutate_text_word(obj, 4, 0xeafffffe),
                   mutate_text_word(obj, 4, 0xfafffffe), mutate_text_word(obj, 4, 0xebfffffd)]
        for mutant in mutants:
            with self.subTest(mutant_sha=sha256(mutant)), self.assertRaises(GateError):
                link_backend.inspect_object(mutant, self.functions[0], 'alpha', {'beta': self.functions[1]})

    def test_malformed_and_out_of_range_relocation_offsets_rejected(self):
        fn, obj = self.functions[0], self.objects[0]
        for offset in (1, len(text_bytes(obj)), 0xffffffff):
            with self.subTest(offset=offset), self.assertRaisesRegex(GateError, 'unsupported/overlapping'):
                link_backend.inspect_object(mutate_relocation(obj, offset=offset), fn,
                                            'alpha', {'beta': self.functions[1]})

    def test_unconfigured_symbol_rejected(self):
        with self.assertRaisesRegex(GateError, 'explicit external'):
            link_backend.inspect_object(self.objects[0], self.functions[0], 'alpha',
                                        {'not_beta': self.functions[1]})

    def test_weak_hidden_object_defined_and_nonentry_symbols_rejected(self):
        obj = self.objects[0]
        for field, value in [('info', 0x20), ('info', 0x11), ('other', 2),
                             ('value', 4), ('size', 4),
                             ('shndx', parse(obj).get_section_index('.text'))]:
            with self.subTest(field=field, value=value), self.assertRaisesRegex(GateError, 'explicit external'):
                link_backend.inspect_object(mutate_call_symbol(obj, field, value),
                                            self.functions[0], 'alpha', {'beta': self.functions[1]})

    def test_unrelocated_bl_blx_and_external_tail_branch_rejected(self):
        leaf, fn = self.objects[3], self.functions[3]
        # The leaf may have three instructions, so B +0 would target its own
        # return. Use a displacement beyond the block for the external-tail case.
        for instruction in (0xebfffffe, 0xfa000000, 0xe12fff30, 0xea000100):
            with self.subTest(instruction=instruction), self.assertRaises(GateError):
                link_backend.inspect_object(mutate_text_word(leaf, 0, instruction), fn, 'delta')

    def test_thumb_cross_module_and_unaligned_targets_rejected(self):
        for target in (dict(self.functions[1], mode='thumb'),
                       dict(self.functions[1], module='other'),
                       dict(self.functions[1], address=BASE + 1)):
            with self.subTest(target=target), self.assertRaisesRegex(GateError, 'same-module ARM'):
                link_backend.inspect_object(self.objects[0], self.functions[0], 'alpha', {'beta': target})

    def test_target_outside_direct_bl_range_rejected(self):
        target = dict(self.functions[1], address=BASE + 0x02000010)
        with self.assertRaisesRegex(GateError, 'outside ARM BL range'):
            link_backend.inspect_object(self.objects[0], self.functions[0], 'alpha', {'beta': target})

    def test_duplicate_symbols_ids_edges_and_unconfigured_targets_rejected(self):
        with self.assertRaisesRegex(GateError, 'duplicate function identity/symbol'):
            self.link(blocks=[(fn, obj, 'same') for fn, obj, _ in self.blocks])
        duplicate_id = list(self.blocks)
        duplicate_id[1] = (dict(duplicate_id[1][0], id='alpha'), duplicate_id[1][1], duplicate_id[1][2])
        with self.assertRaisesRegex(GateError, 'duplicate function identity/symbol'):
            self.link(blocks=duplicate_id)
        with self.assertRaisesRegex(GateError, 'duplicated'):
            self.link(edges={**self.edges, 'alpha': ['beta', 'beta']})
        with self.assertRaisesRegex(GateError, 'not configured'):
            self.link(edges={**self.edges, 'alpha': ['missing']})

    def test_changed_linked_displacement_byte_fails_exact_comparison(self):
        changed = bytearray(self.original)
        changed[4] ^= 1
        functions = [dict(fn) for fn in self.functions]
        functions[0]['target_sha256'] = sha256(changed[:self.sizes[0]])
        blocks = [(fn, obj, symbol) for fn, obj, symbol in
                  zip(functions, self.objects, ('alpha', 'beta', 'gamma', 'delta'))]
        with self.assertRaisesRegex(GateError, 'linked sections differ'):
            self.link(original=bytes(changed), blocks=blocks)

    def test_extra_allocated_section_rejected(self):
        obj = compile_c('int alpha(int x) { return x + 1; } int extra = 9;\n')
        fn = dict(self.functions[0], size=len(text_bytes(obj)), code_size=len(text_bytes(obj)))
        with self.assertRaisesRegex(GateError, 'unaccounted allocated compiler section|object'):
            link_backend.inspect_object(obj, fn, 'alpha')

    def test_exidx_prel31_allowed_only_as_metadata(self):
        rows = [(sec, rel) for sec, rel, _ in rel_records(self.objects[3])
                if parse(self.objects[3]).get_section(sec['sh_info']).name == '.ARM.exidx']
        self.assertTrue(rows)
        self.assertTrue(all(rel['r_info_type'] == 42 for _, rel in rows))
        link_backend.inspect_object(self.objects[3], self.functions[3], 'delta')
        with self.assertRaises(GateError):
            link_backend.inspect_object(mutate_relocation(self.objects[0], kind=42),
                                        self.functions[0], 'alpha', {'beta': self.functions[1]})


class MwccCallBoundaryTests(unittest.TestCase):
    def test_installed_mwcc_rela_pc24_remains_unsupported(self):
        profile = read_json(MWCC_PROFILE_PATH)
        if not (STRICT / profile['executable']).is_file():
            self.skipTest('optional reviewed MWCC executable is not installed')
        obj = compile_c('extern int callee(int); int caller(int x) { return callee(x) + 1; }\n', profile)
        fn = {'id': 'mwcc-caller', 'module': 'synthetic', 'mode': 'arm',
              'address': BASE, 'size': len(text_bytes(obj)), 'code_size': len(text_bytes(obj))}
        calls = [(sec, rel, name) for sec, rel, name in rel_records(obj)
                 if parse(obj).get_section(sec['sh_info']).name == '.text']
        self.assertEqual([rel['r_info_type'] for _, rel, _ in calls], [1])
        self.assertEqual(calls[0][2], 'callee')
        self.assertTrue(calls[0][0].is_RELA())
        with self.assertRaises(GateError):
            link_backend.inspect_object(obj, fn, 'caller', {
                'callee': {'id': 'callee', 'module': 'synthetic', 'mode': 'arm',
                           'address': BASE + 0x100, 'size': 4, 'code_size': 4}})


class CallDeclarationTests(unittest.TestCase):
    def fixture(self, root):
        config = root / 'config' / REVISION
        sources = root / 'src' / 'auto'
        config.mkdir(parents=True)
        sources.mkdir(parents=True)
        profile = config / 'profile.json'
        profile.write_text('{}\n')
        entries, functions = [], []
        for index, symbol in enumerate(('alpha', 'beta')):
            source = sources / (symbol + '.c')
            source.write_text(f'int {symbol}(int x) {{ return x; }}\n')
            functions.append({'id': symbol, 'module': 'arm9', 'mode': 'arm',
                              'address': BASE + index * 8, 'size': 8, 'code_size': 8})
            entries.append({'id': symbol, 'symbol': symbol, 'source': f'src/auto/{symbol}.c',
                            'source_sha256': sha256(source.read_bytes()),
                            'profile': f'config/{REVISION}/profile.json',
                            'profile_sha256': sha256(profile.read_bytes()),
                            'evidence': 'synthetic fixture', 'provenance': 'synthetic fixture'})
        entries[0]['calls'] = ['beta']
        return config, {'schema': 1, 'inventory': 'functions-v1.json', 'functions': entries}, functions

    def test_call_declarations_require_configured_same_module_unique_ids_and_symbols(self):
        cases = ('valid', 'missing', 'cross-module', 'duplicate-edge', 'duplicate-symbol', 'not-list')
        for case in cases:
            with self.subTest(case=case), tempfile.TemporaryDirectory() as td:
                root = Path(td)
                config, plan, functions = self.fixture(root)
                if case == 'missing':
                    plan['functions'][0]['calls'] = ['absent']
                elif case == 'cross-module':
                    functions[1]['module'] = 'arm9/ov000'
                elif case == 'duplicate-edge':
                    plan['functions'][0]['calls'] = ['beta', 'beta']
                elif case == 'duplicate-symbol':
                    plan['functions'][1]['symbol'] = 'alpha'
                elif case == 'not-list':
                    plan['functions'][0]['calls'] = 'beta'
                (config / 'build.json').write_text(json.dumps(plan))
                (config / 'functions-v1.json').write_text(json.dumps({'complete': False, 'functions': functions}))
                if case == 'valid':
                    self.assertEqual(link_backend.validate_declaration(root)[0], plan)
                else:
                    with self.assertRaises(GateError):
                        link_backend.validate_declaration(root)


if __name__ == '__main__':
    unittest.main()
