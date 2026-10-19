"""Synthetic-only regression tests for strict whole-module link gates.

Run with: python3 -B -m unittest discover -s tools/tests -v
No target ROM, repository build output, or original module is read.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

STRICT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(STRICT / 'tools'))

import link_backend
import project
import workflow
from project import GateError, read_json, sha256
from wip_support import compile_bytes, compile_object

PROFILE_PATH = STRICT / 'docs/profiles/clang23-arm946-o2.json'
PROFILE = read_json(PROFILE_PATH)


def compile_source(source: str, *, thumb: bool = False) -> bytes:
    with tempfile.TemporaryDirectory(prefix='pvz-test-c-') as td:
        path = Path(td) / 'candidate.c'
        path.write_text(source)
        profile = dict(PROFILE)
        if thumb:
            profile['flags'] = [('-mthumb' if flag == '-marm' else flag)
                                for flag in PROFILE['flags']]
        obj, _ = compile_object(path, profile)
        return obj


def text_section(obj: bytes):
    from elftools.elf.elffile import ELFFile
    from io import BytesIO
    elf = ELFFile(BytesIO(obj))
    return elf.get_section_by_name('.text')


class LinkBackendSyntheticTests(unittest.TestCase):
    def test_retained_elf_and_complete_module_link(self):
        source = '__attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }\n'
        obj = compile_source(source)
        payload = text_section(obj).data()
        original = b'opaque0!' + payload + b'!opaque1'
        fn = {'id': 'fixture', 'address': 0x02000008, 'size': len(payload),
              'code_size': len(payload), 'target_sha256': sha256(payload)}
        linker_path = Path('/usr/bin/ld.lld')
        linker = {'executable': str(linker_path),
                  'executable_sha256': sha256(linker_path.read_bytes()),
                  'version': subprocess.check_output([str(linker_path), '--version'], text=True).strip()}
        with tempfile.TemporaryDirectory(prefix='pvz-test-link-') as td:
            output = link_backend.link_module(original, 0x02000000, [(fn, obj, 'pvz_fn')],
                                              linker, Path(td) / 'artifacts')
            self.assertEqual(output, original)
            artifacts = Path(td) / 'artifacts'
            self.assertEqual((artifacts / 'module.bin').read_bytes(), original)
            self.assertTrue((artifacts / 'module.elf').is_file())
            self.assertTrue((artifacts / 'module.ld').is_file())
            self.assertTrue((artifacts / 'module.map').is_file())

    def test_wrong_compiled_extent_rejected(self):
        obj = compile_source('__attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }\n')
        size = text_section(obj)['sh_size']
        fn = {'size': size + 4, 'address': 0x02000000, 'code_size': size + 4}
        with self.assertRaisesRegex(GateError, 'complete compiled function size mismatch'):
            link_backend.inspect_object(obj, fn, 'pvz_fn')

    def test_thumb_mode_rejected_by_arm_backend(self):
        obj = compile_source('__attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }\n', thumb=True)
        size = text_section(obj)['sh_size']
        fn = {'size': size, 'address': 0x02000000, 'code_size': size}
        with self.assertRaisesRegex(GateError, 'ARM mapping|wrong instruction mode|function symbol does not exactly cover'):
            link_backend.inspect_object(obj, fn, 'pvz_fn')

    def test_extra_function_rejected(self):
        obj = compile_source('''
            __attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }
            int extra_function(int x) { return x * 3; }
        ''')
        size = text_section(obj)['sh_size']
        fn = {'size': size, 'address': 0x02000000, 'code_size': size}
        with self.assertRaisesRegex(GateError, 'unaccounted allocated compiler section|function symbol'):
            link_backend.inspect_object(obj, fn, 'pvz_fn')

    def test_extra_global_data_rejected(self):
        obj = compile_source('''
            __attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }
            int extra_object = 13;
        ''')
        size = text_section(obj)['sh_size']
        fn = {'size': size, 'address': 0x02000000, 'code_size': size}
        with self.assertRaisesRegex(GateError, 'allocated compiler section|object'):
            link_backend.inspect_object(obj, fn, 'pvz_fn')

    def test_text_relocation_rejected_but_exidx42_is_supported(self):
        natural = compile_source('__attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }\n')
        natural_fn = {'size': text_section(natural)['sh_size'], 'address': 0x02000000,
                      'code_size': text_section(natural)['sh_size']}
        # This also exercises the compiler's SHT_REL exidx metadata relocation 42.
        link_backend.inspect_object(natural, natural_fn, 'pvz_fn')

        external = compile_source('''
            extern int helper(int);
            __attribute__((noinline,used)) int pvz_fn(int x) { return helper(x); }
        ''')
        external_size = text_section(external)['sh_size']
        fn = {'size': external_size, 'address': 0x02000000, 'code_size': external_size}
        with self.assertRaisesRegex(GateError, 'unresolved/text relocation'):
            link_backend.inspect_object(external, fn, 'pvz_fn')

    def test_compile_bytes_uses_immutable_snapshot(self):
        source = b'__attribute__((noinline,used)) int pvz_fn(int x) { return x + 1; }\n'
        with tempfile.TemporaryDirectory(prefix='pvz-snapshot-') as td:
            path = Path(td) / 'candidate.c'
            path.write_bytes(source)
            snapshot = path.read_bytes()
            path.write_text('int pvz_fn(int x) { return x - 7; }\n')
            from_snapshot, _ = compile_bytes(snapshot, PROFILE)
            with tempfile.TemporaryDirectory(prefix='pvz-snapshot-copy-') as td2:
                copy = Path(td2) / 'candidate.c'
                copy.write_bytes(source)
                expected, _ = compile_object(copy, PROFILE)
            self.assertEqual(from_snapshot, expected)
            self.assertNotEqual(from_snapshot, compile_object(path, PROFILE)[0])

    def test_declared_source_and_profile_hashes_are_enforced(self):
        with tempfile.TemporaryDirectory(prefix='pvz-declaration-') as td:
            root = Path(td)
            config = root / 'config' / project.REVISION
            srcdir = root / 'src' / 'auto'
            config.mkdir(parents=True)
            srcdir.mkdir(parents=True)
            source = srcdir / 'fn.c'
            source.write_text('int pvz_fn(int x) { return x; }\n')
            profile = config / 'profile.json'
            profile.write_text(json.dumps(PROFILE))
            fn = {'id': 'fn0', 'module': 'arm9', 'address': 0x02000000,
                  'mode': 'arm', 'size': 8, 'code_size': 8}
            (config / 'functions-v1.json').write_text(json.dumps({'functions': [fn], 'complete': False}))
            item = {'id': 'fn0', 'source': 'src/auto/fn.c', 'source_sha256': '0' * 64,
                    'profile': f'config/{project.REVISION}/profile.json',
                    'profile_sha256': sha256(profile.read_bytes()), 'symbol': 'pvz_fn',
                    'evidence': 'synthetic fixture', 'provenance': 'synthetic fixture'}
            (config / 'build.json').write_text(json.dumps({'schema': 1, 'inventory': 'functions-v1.json',
                                                            'functions': [item]}))
            with self.assertRaisesRegex(GateError, 'stale strict source'):
                link_backend.validate_declaration(root)
            item['source_sha256'] = sha256(source.read_bytes())
            item['profile_sha256'] = '0' * 64
            (config / 'build.json').write_text(json.dumps({'schema': 1, 'inventory': 'functions-v1.json',
                                                            'functions': [item]}))
            with self.assertRaisesRegex(GateError, 'stale strict compiler profile'):
                link_backend.validate_declaration(root)


class ReceiptAndDigestTests(unittest.TestCase):
    def test_verification_receipt_rejects_tampered_or_missing_output(self):
        with tempfile.TemporaryDirectory(prefix='pvz-receipt-') as td:
            root = Path(td)
            output = root / 'build' / workflow.REVISION / 'pvz.nds'
            output.parent.mkdir(parents=True)
            content = b'synthetic exact-ROM stand-in'
            output.write_bytes(content)
            receipt = {'inputs_digest': 'stable-inputs', 'sha1': hashlib.sha1(content).hexdigest(),
                       'sha256': hashlib.sha256(content).hexdigest(), 'full_byte_compare': True,
                       'output': str(output)}
            with (mock.patch.object(workflow, 'ROOT', root),
                  mock.patch.object(workflow, 'inputs_digest', return_value='stable-inputs'),
                  mock.patch.object(workflow, 'ORIGINAL_SHA1', receipt['sha1']),
                  mock.patch.object(workflow, 'ORIGINAL_SHA256', receipt['sha256'])):
                self.assertTrue(workflow.verification_current(receipt))
                output.write_bytes(b'tampered synthetic output')
                self.assertFalse(workflow.verification_current(receipt))
                output.unlink()
                self.assertFalse(workflow.verification_current(receipt))

    def test_materials_digest_covers_compiler_profiles(self):
        with tempfile.TemporaryDirectory(prefix='pvz-materials-') as td:
            root = Path(td)
            for name in ('tools', 'src', 'include', 'config', 'docs/profiles'):
                (root / name).mkdir(parents=True)
            profile = root / 'docs/profiles/compiler.json'
            profile.write_text('{"flags":["-O2"]}\n')
            first = project.materials_digest(root)
            profile.write_text('{"flags":["-O0"]}\n')
            second = project.materials_digest(root)
            self.assertNotEqual(first, second)


if __name__ == '__main__':
    unittest.main(verbosity=2)
