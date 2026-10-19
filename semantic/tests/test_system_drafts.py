"""Unvalidated system drafts remain hash-bound and outside similarity credit."""
import hashlib
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]


class SystemDraftRecords(unittest.TestCase):
    def test_unvalidated_overlay_drafts_have_current_sources_and_explicit_blockers(self):
        record = json.loads((ROOT / 'semantic/evidence/ov000-system-attempts.json').read_text())
        self.assertEqual(record['original_sha1'], 'fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b')
        self.assertFalse(record['semantic_equivalence_proven'])
        for draft in record['drafts']:
            with self.subTest(function=draft['function_id']):
                source = (ROOT / draft['source']).resolve()
                self.assertTrue(source.is_relative_to(ROOT / 'semantic/systems'))
                self.assertEqual(hashlib.sha256(source.read_bytes()).hexdigest(), draft['source_sha256'])
                self.assertTrue(draft['behavior_validation']['status'].startswith('blocked:'))
                self.assertEqual(draft['behavior_validation']['passed_cases'], 0)
                self.assertFalse(draft['behavior_validation']['semantic_equivalence_proven'])
                self.assertFalse(draft['similarity']['strict_credit'])
                self.assertNotIn('tier', draft['similarity'])
                self.assertTrue(draft['next_hypothesis'])
                self.assertLessEqual(draft['code_size'], draft['size'])


if __name__ == '__main__':
    unittest.main()
