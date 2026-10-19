"""Prepare a new public repository without copying private Git history.

Initial release only. Existing destinations and non-document changes are refused.
The source repository, working directories, inputs and remote are left intact.
"""
import sys
sys.dont_write_bytecode = True
import argparse
import json
import os
from pathlib import Path
import subprocess
import tempfile
from project import GateError, ROOT, accepted_functions, git, materials_digest, pipeline_lock
from project import read_json, write_json
from publication_audit import audit, content_issues, path_issues
from workflow import verification_current


def command(root, *args, data=None, env=None):
    return subprocess.check_output(['git', '-C', str(root), *args], input=data, env=env)


def files_at(root, ref):
    result = {}
    for row in command(root, 'ls-tree', '-rz', ref).split(b'\0'):
        if not row:
            continue
        header, path = row.split(b'\t', 1)
        mode, kind, oid = header.split()
        name = path.decode('utf-8')
        if kind != b'blob' or mode not in (b'100644', b'100755') or path_issues(name):
            raise GateError('unsafe release input: ' + name)
        data = command(root, 'cat-file', 'blob', oid.decode())
        if content_issues(data):
            raise GateError('release input needs cleanup: ' + name)
        result[name] = (mode.decode(), data)
    return result


def sanitize(files, private_commits, public_parent=None):
    result = {}
    fields = {'strict_baseline_commit', 'strict_tool_snapshot_commit', 'strict_credit_commit'}
    for name, (mode, raw) in files.items():
        text = raw.decode('utf-8')
        if name.endswith('.md'):
            for oid in private_commits:
                text = text.replace(oid, public_parent or 'pre-public verification snapshot')
        elif name in ('semantic/baseline.json', 'semantic/manifest.json'):
            metadata = json.loads(text)
            for key in fields:
                if key in metadata:
                    if public_parent is None:
                        raise GateError('research metadata requires the verified public parent')
                    metadata[key] = public_parent
            text = json.dumps(metadata, indent=2, sort_keys=True) + '\n'
        if any(oid in text for oid in private_commits):
            raise GateError('private commit reference needs review: ' + name)
        # Runtime/source/configuration bytes must never be changed by this tool.
        if not name.endswith('.md') and name not in ('semantic/baseline.json', 'semantic/manifest.json'):
            if text.encode() != raw:
                raise GateError('unexpected non-document release modification')
        result[name] = (mode, text.encode())
    return result


def make_tree(root, files, env):
    command(root, 'read-tree', '--empty', env=env)
    records = bytearray()
    for name, (mode, data) in sorted(files.items()):
        oid = command(root, 'hash-object', '-w', '--stdin', data=data).decode().strip()
        records.extend(f'{mode} {oid}\t{name}'.encode() + b'\0')
    command(root, 'update-index', '-z', '--index-info', data=bytes(records), env=env)
    return command(root, 'write-tree', env=env).decode().strip()


def prepare(destination):
    destination = destination.resolve()
    if destination.exists() or destination.is_relative_to(ROOT):
        raise GateError('choose a new destination outside the source worktree')
    with pipeline_lock():
        if git('status', '--porcelain'):
            raise GateError('review and commit source work before preparing a release')
        worktrees = git('worktree', 'list', '--porcelain').split('\n\n')
        for entry in worktrees:
            if 'branch refs/heads/wip/semantic' in entry.splitlines():
                tree = Path(entry.splitlines()[0][9:])
                if git('status', '--porcelain', root=tree):
                    raise GateError('research worktree has unreviewed changes')
        receipt = read_json(ROOT / 'build/BWBE-r0/verification.json')
        if not verification_current(receipt):
            raise GateError('current full-ROM verification required before export')
        count = len(accepted_functions())
        private = set(git('rev-list', '--all').splitlines())
        strict = sanitize(files_at(ROOT, 'decomp/strict'), private)
        research_input = files_at(ROOT, 'wip/semantic')
        destination.mkdir(parents=True)
        command(destination, 'init', '-q', '--object-format=sha1', '-b', 'decomp/strict')
        command(destination, 'config', 'core.autocrlf', 'false')
        env = os.environ.copy()
        env.update(GIT_AUTHOR_NAME='lasscat', GIT_COMMITTER_NAME='lasscat',
                   GIT_AUTHOR_EMAIL='lasscat@users.noreply.github.com',
                   GIT_COMMITTER_EMAIL='lasscat@users.noreply.github.com')
        with tempfile.TemporaryDirectory(prefix='pvz-public-index-') as td:
            index_env = dict(env, GIT_INDEX_FILE=str(Path(td) / 'index'))
            tree = make_tree(destination, strict, index_env)
            first = command(destination, '-c', 'commit.gpgsign=false', 'commit-tree', tree,
                            data=b'Initialize verified Plants vs. Zombies DS reconstruction\n', env=env).decode().strip()
            command(destination, 'update-ref', 'refs/heads/decomp/strict', first, '0' * 40)
            research = sanitize(research_input, private, first)
            tree = make_tree(destination, research, index_env)
            second = command(destination, '-c', 'commit.gpgsign=false', 'commit-tree', tree, '-p', first,
                             data=b'Add readable research drafts and scoped behavior tests\n', env=env).decode().strip()
            command(destination, 'update-ref', 'refs/heads/wip/semantic', second, '0' * 40)
        # Materialize only the verified tree. No checkout/reset touches source work.
        for name, (mode, data) in strict.items():
            path = destination / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
            path.chmod(0o755 if mode == '100755' else 0o644)
        command(destination, 'read-tree', first)
        command(destination, 'tag', 'strict/' + str(count) + 'funcs', first)
        if materials_digest(destination) != materials_digest(ROOT):
            raise GateError('verified build materials changed in public copy; do not publish')
        reachable = set(command(destination, 'rev-list', '--all').decode().splitlines())
        if reachable & private or len(reachable) != 2:
            raise GateError('unexpected history in public copy; do not publish')
        report = audit(destination)
        if not report['passed'] or report['history']['historical_home_path_blobs']:
            raise GateError('public copy failed publication audit; preserve it for diagnosis')
        if command(destination, 'status', '--porcelain').strip():
            raise GateError('public copy has unexpected uncommitted files')
        write_json(ROOT / 'build/local/public-cleanup/export-report.json',
                   {'destination': str(destination), 'public_heads': report['heads'],
                    'private_commits_copied': 0, 'build_materials_identical': True,
                    'audit': report})
        print(json.dumps({'destination': str(destination), 'heads': report['heads'],
                          'private_commits_copied': 0, 'build_materials_identical': True}, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--destination', type=Path, required=True)
    args = parser.parse_args()
    try:
        prepare(args.destination)
        return 0
    except (GateError, OSError, ValueError, subprocess.SubprocessError) as exc:
        print('PUBLIC PREPARATION FAILED: ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
