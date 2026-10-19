"""Saved supplemental behavior records are hash-bound, not S/B credit."""
import copy
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'semantic/tools'))
from rng_lifecycle_check import REPORT, GateError, read_json, validate_report


class RngLifecycleRecordTests(unittest.TestCase):
    def test_saved_record_is_current_but_not_equivalence_or_strict_credit(self):
        report = read_json(REPORT)
        self.assertEqual(validate_report(report)['passed_calls'], 1263)
        self.assertFalse(report['semantic_equivalence_proven'])
        self.assertTrue(report['strict_status'].startswith('blocked:'))
        self.assertEqual(report['paired_draws'], 626)
        self.assertGreater(report['raw_high_bit_set_draws'], 0)

    def test_stale_source_model_case_count_and_failure_controls_rejected(self):
        saved = read_json(REPORT)
        for case in ('source', 'model', 'count', 'memory', 'control', 'proof'):
            report = copy.deepcopy(saved)
            if case == 'source':
                report['bindings']['semantic/systems/rng_lifecycle.c'] = '0' * 64
            elif case == 'model':
                report['bindings']['semantic/tools/arm_call_cluster.py'] = '0' * 64
            elif case == 'count':
                report['passed_calls'] += 1
            elif case == 'memory':
                report['cases'][0]['full_states_and_guards_equal'] = False
            elif case == 'control':
                report['negative_controls']['wrong_memory']['detected'] = False
            else:
                report['semantic_equivalence_proven'] = True
            with self.subTest(case=case), self.assertRaises(GateError):
                validate_report(report)


if __name__ == '__main__':
    unittest.main()
