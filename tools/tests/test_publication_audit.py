"""Publication checks use isolated synthetic Git repositories, never game inputs."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from publication_audit import REQUIRED, audit, content_issues, path_issues


class PublicationAuditTests(unittest.TestCase):
    def git(self, root, *args):
        return subprocess.check_output(['git', '-C', str(root), *args], stderr=subprocess.STDOUT)

    def commit(self, root):
        self.git(root, 'add', '--all')
        self.git(root, '-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid',
                 'commit', '-qm', 'Synthetic fixture')

    def repository(self, root):
        self.git(root, 'init', '-q', '-b', 'decomp/strict')
        for name in REQUIRED:
            path = root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('Synthetic publication fixture.\n')
        self.commit(root)
        self.git(root, 'branch', 'wip/semantic')

    def test_clean_repository_is_read_only(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.repository(root)
            before = self.git(root, 'status', '--porcelain')
            heads = self.git(root, 'show-ref')
            result = audit(root, worktree=True)
            self.assertTrue(result['passed'])
            self.assertEqual(before, self.git(root, 'status', '--porcelain'))
            self.assertEqual(heads, self.git(root, 'show-ref'))

    def test_retired_credential_still_blocks_history(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.repository(root)
            token = 'gh' + 'p_' + 'A' * 40
            path = root / 'old-notes.txt'
            path.write_text(token)
            self.commit(root)
            path.write_text('Removed from the current tree.\n')
            self.commit(root)
            result = audit(root)
            self.assertTrue(all(not tree['blockers'] for tree in result['trees']))
            self.assertFalse(result['passed'])
            self.assertIn('credential_pattern', [row['kind'] for row in result['history']['blockers']])
            self.assertNotIn(token, str(result))

    def test_binary_without_extension_is_rejected(self):
        self.assertIn('binary_content', content_issues(b'\x7fELF\0synthetic'))
        self.assertIn('forbidden_input_path', path_issues('tools/bin/runner'))
        self.assertIn('forbidden_input_path', path_issues('renamed.nds'))
        self.assertIn('environment_file', path_issues('.env.production'))

    def test_home_paths_block_heads_but_are_reported_in_history(self):
        path = ('/' + 'home/' + 'example/' + 'project').encode()
        self.assertIn('machine_home_path', content_issues(path))
        self.assertNotIn('machine_home_path', content_issues(path, history=True))

    def test_worktree_symlink_and_missing_document_are_rejected(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.repository(root)
            (root / 'alias').symlink_to('README.md')
            result = audit(root, worktree=True)
            self.assertFalse(result['passed'])
            self.assertIn('non_regular_worktree_input', [r['kind'] for r in result['worktree_blockers']])
            (root / 'alias').unlink()
            (root / 'NOTICE.md').unlink()
            self.commit(root)
            result = audit(root)
            self.assertFalse(result['passed'])
            self.assertIn('missing_publication_document', [r['kind'] for r in result['trees'][0]['blockers']])


if __name__ == '__main__':
    unittest.main()
