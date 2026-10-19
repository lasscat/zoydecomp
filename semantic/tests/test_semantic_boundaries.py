import copy
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'semantic/tools'))
from project import GateError, read_json, sha256, load_universe
from semantic_progress import validate_candidate
from arm_subset import Arm, Region, Unsupported
from progress_support import saved_progress, behavior_evidence


class LogicAndBankBoundaries(unittest.TestCase):
    def test_cmp_signed_overflow_and_unsigned_carry(self):
        cpu = Arm([])
        cpu.cmp(0x80000000, 1)
        self.assertTrue(cpu.v)
        self.assertTrue(cpu.condition(11))  # signed LT despite nonnegative wrapped result
        self.assertTrue(cpu.c)
        cpu.cmp(0xffffffff, 0xffffffff)
        self.assertTrue(cpu.z)
        self.assertTrue(cpu.c)
        self.assertFalse(cpu.condition(11))
        cpu.cmp(0, 0xffffffff)
        self.assertFalse(cpu.c)
        self.assertFalse(cpu.condition(11))

    def test_readonly_unmapped_and_unknown_instruction_fail(self):
        cpu = Arm([Region(0x1000, bytearray((0xef000000).to_bytes(4, 'little')), False)])
        with self.assertRaisesRegex(Unsupported, 'readonly'):
            cpu.store(0x1000, 0)
        with self.assertRaisesRegex(Unsupported, 'unmapped'):
            cpu.load(0x2000)
        cpu.r[15] = 0x1000
        with self.assertRaisesRegex(Unsupported, 'unsupported ARM instruction'):
            cpu.step()

    def test_stale_source_rejected(self):
        item = copy.deepcopy(read_json(ROOT / 'semantic/candidates.json')['candidates'][0])
        item['source_sha256'] = '0' * 64
        with self.assertRaisesRegex(GateError, 'stale source'):
            validate_candidate(item)

    def test_source_escape_rejected(self):
        item = copy.deepcopy(read_json(ROOT / 'semantic/candidates.json')['candidates'][0])
        item['source'] = 'tools/project.py'
        with self.assertRaisesRegex(GateError, 'escapes'):
            validate_candidate(item)

    def test_instruction_limit(self):
        # Synthetic branch-to-self fixture; no target instruction bytes.
        cpu = Arm([Region(0x1000, bytearray((0xeafffffe).to_bytes(4, 'little')), False)])
        cpu.r[15] = 0x1000
        with self.assertRaisesRegex(Unsupported, 'limit'):
            cpu.run(0x2000, limit=3)

    def test_counter_inconsistency_rejected(self):
        import shutil
        from project import write_json
        manifest = read_json(ROOT / 'semantic/manifest.json')
        manifest['counters']['B_union_S_functions'] += 1
        with tempfile.TemporaryDirectory() as td:
            tree = Path(td)
            paths = list(manifest['tool_hashes'])
            for item in manifest['best']:
                paths.extend([item['source'], item['profile_path']])
            for name in set(paths):
                p = tree / name
                p.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(ROOT / name, p)
            path = tree / 'semantic/manifest.json'
            write_json(path, manifest)
            with self.assertRaisesRegex(GateError, 'counter inconsistency'):
                saved_progress(path, load_universe())

    def seed_evidence(self):
        return copy.deepcopy(next(item for item in read_json(ROOT / 'semantic/manifest.json')['best']
                                  if item['function_id'] == 'arm9:02034f40:arm'))

    def test_behavior_is_independent_of_similarity(self):
        item = self.seed_evidence()
        self.assertEqual(item['metrics']['tier'], 'X')
        evidence = behavior_evidence(item, ROOT)
        self.assertEqual(evidence['passed_cases'], 41)
        self.assertEqual(evidence['transition_scenarios'], 4)
        self.assertFalse(evidence['equivalence_proven'])
        self.assertEqual(item['metrics']['tier'], 'X')

    def test_behavior_wrong_target_rejected(self):
        item = self.seed_evidence()
        item['function']['target_sha256'] = '0' * 64
        with self.assertRaisesRegex(GateError, 'binding'):
            behavior_evidence(item, ROOT)

    def behavior_fixture(self, root):
        import shutil
        for name in ('semantic/behavior/mt_seed.json', 'semantic/tools/behavior_check.py',
                     'semantic/tools/arm_subset.py'):
            path = root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(ROOT / name, path)

    def test_behavior_stale_harness_rejected(self):
        item = self.seed_evidence()
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.behavior_fixture(root)
            (root / 'semantic/tools/behavior_check.py').write_text('changed harness')
            with self.assertRaisesRegex(GateError, 'stale behavior harness'):
                behavior_evidence(item, root)

    def test_behavior_case_count_is_validated(self):
        from project import write_json
        item = self.seed_evidence()
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.behavior_fixture(root)
            path = root / item['behavior_validation']['report']
            report = read_json(path)
            report['passed_cases'] += 1
            write_json(path, report)
            item['behavior_validation']['report_sha256'] = sha256(path.read_bytes())
            with self.assertRaisesRegex(GateError, 'inconsistent or unscoped'):
                behavior_evidence(item, root)

    def run_bad_native_predicate(self, body, expected_error):
        import ctypes as C
        import subprocess
        from behavior_check import compare_predicate_case
        profile = read_json(ROOT / 'semantic/profiles/clang23-arm946-o2.json')
        self.assertEqual(sha256(Path(profile['executable']).read_bytes()), profile['executable_sha256'])
        with tempfile.TemporaryDirectory() as td:
            work = Path(td)
            (work / 'bad.c').write_text('int bad(void *owner) {' + body + '}\n')
            subprocess.run([profile['executable'], '-shared', '-fPIC', '-O2',
                            str(work / 'bad.c'), '-o', str(work / 'bad.so')], check=True)
            library = C.CDLL(str(work / 'bad.so'))
            native = library.bad
            native.argtypes, native.restype = [C.c_void_p], C.c_int
            # Synthetic MOV r0,#1; BX LR fixture; no original game bytes.
            target = bytes.fromhex('0100a0e31eff2fe1')
            with self.assertRaisesRegex(GateError, expected_error):
                compare_predicate_case({'address': 0x02000000}, target, native, 1)

    def test_wrong_compiled_c_return_is_detected(self):
        self.run_bad_native_predicate('return 0;', 'return discrepancy')

    def test_wrong_compiled_c_memory_effect_is_detected(self):
        self.run_bad_native_predicate('((unsigned char *)owner)[0] ^= 1; return 1;',
                                      'memory/guard discrepancy')

    def test_unsigned_predicate_conditions(self):
        cpu = Arm([])
        for value, limit, hi, ls in [(0xffffffff, 2, True, False), (0, 2, False, True),
                                     (2, 2, False, True), (3, 2, True, False)]:
            cpu.cmp(value, limit)
            self.assertEqual(cpu.condition(8), hi)
            self.assertEqual(cpu.condition(9), ls)

    def test_missing_behavior_status_rejected(self):
        item = copy.deepcopy(read_json(ROOT / 'semantic/candidates.json')['candidates'][0])
        item.pop('behavior_validation')
        with self.assertRaisesRegex(GateError, 'explicit behavior status'):
            validate_candidate(item)

    def test_new_data_processing_ops(self):
        # Synthetic ARM only: mov r0,#5; subs r0,r0,#1; tst r0,#4; bic r1,r0,#1; orr r2,r1,#8.
        code = bytes.fromhex('0500a0e3' '010050e2' '041000e3' '0110c0e3' '082081e3')
        cpu = Arm([Region(0x1000, bytearray(code), False)])
        cpu.r[15] = 0x1000
        cpu.step()                       # mov r0, #5
        self.assertEqual(cpu.r[0], 5)
        cpu.step()                       # subs r0, r0, #1 -> 4 with C=1
        self.assertEqual(cpu.r[0], 4)
        self.assertFalse(cpu.z)
        self.assertTrue(cpu.c)
        cpu.step()                       # tst r0, #4 -> nonzero, Z clear
        self.assertFalse(cpu.z)
        self.assertEqual(cpu.r[0], 4)
        cpu.step()                       # bic r1, r0, #1 -> 4
        self.assertEqual(cpu.r[1], 4)
        cpu.step()                       # orr r2, r1, #8 -> 12
        self.assertEqual(cpu.r[2], 12)

    def test_wrong_mt_next_return_is_detected(self):
        import ctypes as C
        import subprocess
        from behavior_check import compare_next_sequence, fixed_state
        # Synthetic ARM only: mov r0,#42; bx lr. No original game bytes.
        target = bytes.fromhex('2a00a0e31eff2fe1')
        base = 0x02281000
        size = 64 + 2504 + 64
        initial = bytearray((i * 13 + 7) & 255 for i in range(size))
        initial[64:68] = (5).to_bytes(4, 'little')
        initial[68:72] = (base + 8).to_bytes(4, 'little')
        initial = bytes(initial)
        profile = read_json(ROOT / 'semantic/profiles/clang23-arm946-o2.json')
        self.assertEqual(sha256(Path(profile['executable']).read_bytes()), profile['executable_sha256'])
        with tempfile.TemporaryDirectory() as td:
            work = Path(td)
            (work / 'bad.c').write_text('unsigned int pvz_mt_next(void *state) {(void)state; return 0u;}\n')
            subprocess.run([profile['executable'], '-shared', '-fPIC', '-O2', '-std=c11',
                            str(work / 'bad.c'), '-o', str(work / 'bad.so')], check=True)
            library = C.CDLL(str(work / 'bad.so'))
            bad = library.pvz_mt_next
            bad.argtypes, bad.restype = [C.c_void_p], C.c_uint32
            buffer = fixed_state(base, size)
            with self.assertRaisesRegex(GateError, 'return discrepancy'):
                compare_next_sequence(base, buffer, {'address': 0}, b'', {'address': 0x02000000},
                                      target, None, bad, [('next',)], initial, 0)


if __name__ == '__main__':
    unittest.main()
