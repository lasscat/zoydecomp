"""Explicit authorized GitHub publication; excludes legal binary inputs, never forces."""
import argparse
from pathlib import Path
import subprocess
from project import GateError, ROOT, git, pipeline_lock
import rom


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository', default='lasscat/zoydecomp')
    parser.add_argument('--rom', required=True, type=Path)
    parser.add_argument('--create-private', action='store_true')
    args = parser.parse_args()
    if args.repository != 'lasscat/zoydecomp':
        raise GateError('Review a different repository destination before publication')
    with pipeline_lock():
        if git('status', '--porcelain'):
            raise GateError('Review and commit explicit project files before publishing')
        for branch in ('decomp/strict', 'wip/semantic'):
            for p in git('ls-tree', '-r', '--name-only', branch).splitlines():
                if any(x in p.split('/') for x in ('rom', 'extract', 'build', 'reference', 'bin')):
                    raise GateError('forbidden publication input: ' + p)
                if Path(p).suffix.lower() in ('.nds', '.srl', '.bin', '.o', '.elf', '.exe', '.dll', '.a', '.so'):
                    raise GateError('binary publication input: ' + p)
        rom.verify(args.rom)
        subprocess.run(['gh', 'auth', 'status'], check=True)
        if args.create_private:
            subprocess.run(['gh', 'repo', 'create', args.repository, '--private',
                            '--description', 'PvZ DS verified binary baseline and separate reconstruction research'],
                           check=True)
        url = 'https://github.com/' + args.repository + '.git'
        existing = git('remote').splitlines()
        if 'origin' in existing:
            if git('remote', 'get-url', 'origin') != url:
                raise GateError('origin points elsewhere; preserve it and review')
        else:
            subprocess.run(['git', '-C', str(ROOT), 'remote', 'add', 'origin', url], check=True)
        subprocess.run(['git', '-C', str(ROOT), 'push', '--atomic', '-u', 'origin',
                        'decomp/strict', 'wip/semantic'], check=True)
        refs = subprocess.check_output(['git', '-C', str(ROOT), 'ls-remote', 'origin',
                                        'refs/heads/decomp/strict', 'refs/heads/wip/semantic'], text=True)
        remote = {ref: sha for sha, ref in (line.split() for line in refs.splitlines())}
        for branch in ('decomp/strict', 'wip/semantic'):
            if remote.get('refs/heads/' + branch) != git('rev-parse', branch):
                raise GateError('remote head verification failed: ' + branch)
        print('Published and verified both remote branch heads: ' + url)


if __name__ == '__main__':
    main()
