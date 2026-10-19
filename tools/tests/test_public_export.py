"""Privacy and source-preservation checks for initial public snapshots."""
from pathlib import Path
import json
import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from prepare_public import command, files_at, make_tree, sanitize
from project import GateError


class PublicExportTests(unittest.TestCase):
    def test_only_document_references_and_research_provenance_change(self):
        old, new = 'a' * 40, 'b' * 40
        source = b'unsigned example(unsigned value) { return value + 1; }\n'
        files = {'src/auto/example.c': ('100644', source),
                 'README.md': ('100644', ('Verified before release at ' + old).encode()),
                 'semantic/baseline.json': ('100644', json.dumps(
                     {'strict_baseline_commit': old, 'original_sha256': 'c' * 64}).encode())}
        public = sanitize(files, {old}, new)
        self.assertEqual(public['src/auto/example.c'][1], source)
        metadata = json.loads(public['semantic/baseline.json'][1])
        self.assertEqual(metadata['strict_baseline_commit'], new)
        self.assertEqual(metadata['original_sha256'], 'c' * 64)
        self.assertNotIn(old.encode(), public['README.md'][1])

    def test_private_reference_in_runtime_input_stops_export(self):
        old = 'a' * 40
        with self.assertRaisesRegex(GateError, 'private commit reference'):
            sanitize({'config/settings.json': ('100644', json.dumps({'unexpected': old}).encode())}, {old})

    def test_new_tree_preserves_exact_file_bytes_and_modes(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            command(root, 'init', '-q', '--object-format=sha1', '-b', 'decomp/strict')
            files = {'README.md': ('100644', b'Synthetic release fixture.\n'),
                     'tools/example.py': ('100755', b'print("synthetic fixture")\n')}
            env = dict(os.environ, GIT_INDEX_FILE=str(root / '.git/test-index'),
                       GIT_AUTHOR_NAME='Fixture', GIT_AUTHOR_EMAIL='fixture@example.invalid',
                       GIT_COMMITTER_NAME='Fixture', GIT_COMMITTER_EMAIL='fixture@example.invalid')
            tree = make_tree(root, files, env)
            commit = command(root, '-c', 'commit.gpgsign=false', 'commit-tree', tree,
                             data=b'Synthetic fixture\n', env=env).decode().strip()
            self.assertEqual(files_at(root, commit), files)
            self.assertEqual(len(command(root, 'rev-list', commit).splitlines()), 1)


if __name__ == '__main__':
    unittest.main()
