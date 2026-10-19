"""Read-only publication audit of both tracks and reachable Git history.

Reports locations and object IDs, never matched credential values. This is a
bounded pattern/content check, not a guarantee that every secret can be recognized.
"""
import sys
sys.dont_write_bytecode = True
import argparse
import json
from pathlib import Path, PurePosixPath
import re
import subprocess
from project import GateError, ROOT

BRANCHES = ('decomp/strict', 'wip/semantic')
REQUIRED = ('LICENSE', 'NOTICE.md', 'README.md', 'CONTRIBUTING.md', 'AGENTS.md',
            'docs/publishing.md')
FORBIDDEN_PARTS = {'rom', 'extract', 'build', 'reference', 'bin', 'sdk', '.ssh', '.aws',
                   '.codex', '.agents', '.private', 'private', 'local'}
FORBIDDEN_SUFFIXES = {'.nds', '.srl', '.bin', '.o', '.elf', '.exe', '.dll', '.a', '.so',
                      '.zip', '.7z', '.tar', '.gz', '.pem', '.key', '.p12', '.pfx'}
SECRETS = re.compile(rb'gh[pousr]_[A-Za-z0-9]{20,}|github_pat_[A-Za-z0-9_]{30,}'
                     rb'|AKIA[A-Z0-9]{16}|-----BEGIN (?:[A-Z ]* )?PRIVATE KEY-----')
HOME_PATH = re.compile(rb'/(?:home|Users)/[^/\s]+/')


def git_bytes(root, *args):
    return subprocess.check_output(['git', '-C', str(root), *args])


def path_issues(name):
    path = PurePosixPath(name)
    parts = {part.lower() for part in path.parts}
    issues = []
    if parts & FORBIDDEN_PARTS or path.suffix.lower() in FORBIDDEN_SUFFIXES:
        issues.append('forbidden_input_path')
    if path.name.lower() == '.env' or path.name.lower().startswith('.env.'):
        issues.append('environment_file')
    return issues


def content_issues(data, *, history=False):
    issues = []
    if SECRETS.search(data):
        issues.append('credential_pattern')
    try:
        data.decode('utf-8')
    except UnicodeDecodeError:
        issues.append('non_text_blob')
    if b'\0' in data or data.startswith((b'MZ', b'\x7fELF', b'PK\x03\x04')):
        issues.append('binary_content')
    if not history and HOME_PATH.search(data):
        issues.append('machine_home_path')
    return issues


def resolve(root, branch):
    for ref in ('refs/heads/' + branch, 'refs/remotes/origin/' + branch):
        result = subprocess.run(['git', '-C', str(root), 'rev-parse', '--verify', ref + '^{commit}'],
                                capture_output=True, text=True)
        if result.returncode == 0:
            return result.stdout.strip()
    raise GateError('missing required publication branch: ' + branch)


def scan_tree(root, branch, commit):
    findings, names = [], set()
    tree = git_bytes(root, 'ls-tree', '-rz', commit)
    for record in tree.split(b'\0'):
        if not record:
            continue
        header, path = record.split(b'\t', 1)
        mode, kind, oid = header.split()
        name = path.decode('utf-8')
        names.add(name)
        issues = path_issues(name)
        if mode not in (b'100644', b'100755') or kind != b'blob':
            issues.append('non_regular_git_entry')
        else:
            issues += content_issues(git_bytes(root, 'cat-file', 'blob', oid.decode()))
        findings += [{'kind': issue, 'path': name} for issue in sorted(set(issues))]
    findings += [{'kind': 'missing_publication_document', 'path': name}
                 for name in REQUIRED if name not in names]
    return {'branch': branch, 'commit': commit, 'files': len(names), 'blockers': findings}


def scan_history(root):
    # Batch access scans blobs once, including reachable tags/remote refs. No reset,
    # checkout, index mutation, network request or history rewriting occurs.
    rows = git_bytes(root, 'rev-list', '--objects', '--all').decode().splitlines()
    findings, homes, blobs = [], 0, 0
    process = subprocess.Popen(['git', '-C', str(root), 'cat-file', '--batch'],
                               stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    try:
        for row in rows:
            oid, _, name = row.partition(' ')
            process.stdin.write((oid + '\n').encode())
            process.stdin.flush()
            header = process.stdout.readline().split()
            if len(header) != 3 or header[0].decode() != oid:
                raise GateError('Git object batch failed')
            data = process.stdout.read(int(header[2]))
            if process.stdout.read(1) != b'\n' or len(data) != int(header[2]):
                raise GateError('truncated Git object')
            if header[1] != b'blob':
                continue
            blobs += 1
            homes += bool(HOME_PATH.search(data))
            issues = content_issues(data, history=True) + path_issues(name)
            findings += [{'kind': issue, 'object': oid, 'path': name}
                         for issue in sorted(set(issues))]
    finally:
        process.stdin.close()
        process.stdout.close()
        if process.wait() != 0:
            raise GateError('Git history object reader failed')
    return {'blobs': blobs, 'blockers': findings, 'historical_home_path_blobs': homes,
            'note': 'History/author metadata is retained; historical machine paths are reported, not rewritten.'}


def audit(root=ROOT, history=True, worktree=False):
    heads = {branch: resolve(root, branch) for branch in BRANCHES}
    trees = [scan_tree(root, branch, commit) for branch, commit in heads.items()]
    old = scan_history(root) if history else None
    current = []
    if worktree:
        names = git_bytes(root, 'ls-files', '-z', '--cached', '--others', '--exclude-standard')
        for raw in set(names.split(b'\0')) - {b''}:
            name = raw.decode('utf-8')
            path = root / name
            if path.is_symlink() or not path.is_file():
                current.append({'kind': 'non_regular_worktree_input', 'path': name})
                continue
            current += [{'kind': issue, 'path': name} for issue in
                        path_issues(name) + content_issues(path.read_bytes())]
    return {'schema': 1, 'heads': heads, 'trees': trees, 'history': old,
            'worktree_blockers': current,
            'passed': not (any(t['blockers'] for t in trees) or current
                           or old is not None and old['blockers'])}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--worktree', action='store_true', help='also check proposed current-worktree files')
    args = parser.parse_args()
    try:
        result = audit(worktree=args.worktree)
        print(json.dumps(result, indent=2))
        return 0 if result['passed'] else 2
    except (GateError, OSError, ValueError, subprocess.SubprocessError) as exc:
        print('PUBLICATION AUDIT ERROR: ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
