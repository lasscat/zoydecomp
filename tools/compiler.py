"""Discover legal local MWCC installations and explicitly pin optional profiles.

Discovery is read-only. Profile creation never changes strict build declarations.
No downloads, original-compiler guesses, automatic flag sweeps or QEMU fallback.
"""
import sys
sys.dont_write_bytecode = True
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
from project import GateError, ROOT, sha256, write_json
from mwcc_support import MEASURED_FLAGS


def discover(roots):
    found = {}
    for root in roots:
        root = Path(root).expanduser()
        if not root.exists():
            continue
        candidates = [root] if root.is_file() else root.rglob('*')
        for path in candidates:
            if path.is_file() and path.name.lower() in ('mwccarm', 'mwccarm.exe'):
                path = path.resolve()
                found[str(path)] = {'executable': str(path),
                                    'executable_sha256': sha256(path.read_bytes())}
    return [found[name] for name in sorted(found)]


def pin(path):
    path = Path(path).resolve(strict=True)
    return {'executable': str(path), 'executable_sha256': sha256(path.read_bytes())}


def make_profile(compiler, runner=None, qemu=None, thumb=False):
    chain = []
    if qemu:
        if not runner:
            raise GateError('explicit QEMU mode requires an explicit wibo runner')
        record = pin(qemu)
        version = subprocess.run([record['executable'], '--version'], capture_output=True,
                                 text=True, timeout=20, check=True)
        record.update(version_args=['--version'], version=version.stdout.strip())
        chain.append(record)
    if runner:
        chain.append(pin(runner))
    identity = pin(compiler)
    argv = [r['executable'] for r in chain] + [identity['executable']]
    version = subprocess.run([*argv, '-version'], capture_output=True, text=True, timeout=20)
    if version.returncode:
        raise GateError('native/selected runner failed (status ' + str(version.returncode)
                        + '); no automatic QEMU fallback. Fix the native runner or explicitly select --qemu.')
    help_result = subprocess.run([*argv, '-help'], capture_output=True, text=True, timeout=20)
    help_text = help_result.stdout + help_result.stderr
    option_text = help_text.replace('[no]', '')
    if help_result.returncode or any(flag not in option_text for flag in
                                      ('-proc', '-O', '-fp', '-little', '-thumb')):
        raise GateError('compiler help does not establish supported options; review manually')
    return dict(identity, driver='mwcc-standalone-c-v1', version=version.stdout.strip(),
                version_stderr=version.stderr, runner_chain=chain,
                flags=list(MEASURED_FLAGS) + ['-thumb' if thumb else '-nothumb'], symbol_values={},
                help_sha256=sha256(help_text.encode()),
                provenance='Exploratory installed compiler; option names checked against help; measured flags require per-function evidence. Not original-compiler identification.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('discover', 'profile'))
    parser.add_argument('--search-root', type=Path, action='append', default=[])
    parser.add_argument('--compiler', type=Path)
    parser.add_argument('--runner', type=Path)
    parser.add_argument('--qemu', type=Path, help='explicit opt-in; never selected automatically')
    parser.add_argument('--thumb', action='store_true')
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    try:
        roots = args.search_root or [Path(os.environ.get('PVZ_MWCC_ROOT', ROOT / 'tools/bin/mwccarm'))]
        installed = discover(roots)
        if args.command == 'discover':
            print(json.dumps({'compilers': installed, 'native_wibo_on_path': shutil.which('wibo'),
                              'qemu_automatic': False}, indent=2))
            return 0
        compiler = args.compiler
        if compiler is None:
            if len(installed) != 1:
                raise GateError('expected one discovered compiler; select --compiler explicitly')
            compiler = Path(installed[0]['executable'])
        if args.output is None:
            raise GateError('profile requires an explicit --output; start in private scratch')
        output = args.output.resolve()
        if ((output.is_relative_to(ROOT) and not output.is_relative_to(ROOT / 'build/local'))
                or not (output.is_relative_to(Path('/tmp'))
                        or output.is_relative_to(ROOT / 'build/local'))):
            raise GateError('profile output must be private scratch or ignored build/local; bank metadata through review')
        if args.output.exists():
            raise GateError('preserving existing profile; choose a new output path')
        local_runner = ROOT / 'tools/bin/wibo'
        runner = args.runner or (local_runner if local_runner.is_file() else shutil.which('wibo'))
        profile = make_profile(compiler, runner, args.qemu, args.thumb)
        write_json(args.output, profile)
        print('PINNED optional profile: ' + str(args.output) + '; strict settings unchanged')
        return 0
    except (GateError, OSError, ValueError, subprocess.SubprocessError) as exc:
        print('COMPILER ERROR: ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
