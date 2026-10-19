"""Optional driver/discovery boundaries using a clearly synthetic CLI shim."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import compiler
from project import GateError, sha256
from wip_support import compile_bytes, extract_text


class OptionalCompilerTests(unittest.TestCase):
    def test_profile_cannot_write_tracked_configuration(self):
        with mock.patch('sys.argv', ['compiler.py', 'profile', '--compiler', '/unused/compiler',
                                    '--output', str(compiler.ROOT / 'config/unsafe.json')]):
            with mock.patch('compiler.make_profile') as make:
                self.assertEqual(compiler.main(), 2)
                make.assert_not_called()

    def test_discovery_is_read_only_and_deduplicates(self):
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'mwccarm.exe'
            path.write_bytes(b'synthetic discovery input; never executed')
            before = path.read_bytes()
            rows = compiler.discover([Path(td), Path(td)])
            self.assertEqual(len(rows), 1)
            self.assertEqual(rows[0]['executable_sha256'], sha256(before))
            self.assertEqual(path.read_bytes(), before)

    def test_native_failure_never_selects_qemu(self):
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'mwccarm.exe'
            path.write_bytes(b'synthetic')
            with mock.patch('compiler.subprocess.run', return_value=subprocess.CompletedProcess(
                    [], 159, '', 'synthetic native failure')) as run:
                with self.assertRaisesRegex(GateError, 'no automatic QEMU fallback'):
                    compiler.make_profile(path)
                self.assertEqual(run.call_count, 1)
                self.assertEqual(run.call_args.args[0], [str(path), '-version'])

    def test_optional_driver_snapshot_and_identity(self):
        # This shim translates the reviewed CLI to native Clang for a synthetic
        # function. It tests orchestration, not real MWCC code generation.
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'mwccarm'
            path.write_text('#!' + sys.executable + '\n' + '''
import subprocess, sys
if sys.argv[1:] == ['-version']:
    print('synthetic MWCC CLI shim; not a real compiler')
elif sys.argv[1:] == ['-help']:
    print('-proc -O -fp -little -thumb')
else:
    output = sys.argv[sys.argv.index('-o') + 1]
    raise SystemExit(subprocess.run(['/usr/bin/clang', '--target=arm-none-eabi',
        '-mcpu=arm946e-s', '-marm', '-O2', '-ffreestanding', '-c', 'candidate.c',
        '-o', output]).returncode)
''')
            path.chmod(0o755)
            profile = compiler.make_profile(path)
            self.assertEqual(profile['runner_chain'], [])
            obj, _ = compile_bytes(b'unsigned pvz_fixture(unsigned value) { return value + 1; }\n', profile)
            self.assertTrue(extract_text(obj, {}))
            bad_flags = dict(profile, flags=['-unreviewed'])
            with self.assertRaisesRegex(GateError, 'unreviewed MWCC flags'):
                compile_bytes(b'unsigned pvz_fixture(void) { return 0; }\n', bad_flags)
            path.write_text('changed executable')
            with self.assertRaisesRegex(GateError, 'compiler identity changed'):
                compile_bytes(b'unsigned pvz_fixture(void) { return 0; }\n', profile)


if __name__ == '__main__':
    unittest.main()
