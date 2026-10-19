"""Optional pinned MWCC standalone driver. No implicit emulator fallback."""
from pathlib import Path
import subprocess
import tempfile
from project import GateError, ROOT, sha256

MEASURED_FLAGS = ('-proc', 'arm946e', '-O2', '-fp', 'soft', '-little')
INTERWORKING_FLAGS = MEASURED_FLAGS + ('-nothumb', '-interworking')


def command(profile):
    result = []

    def resolve(name):
        path = Path(name)
        return path if path.is_absolute() else ROOT / path

    for record in profile.get('runner_chain', []):
        path = resolve(record['executable'])
        if sha256(path.read_bytes()) != record['executable_sha256']:
            raise GateError('compiler runner identity changed')
        if record.get('version_args'):
            check = subprocess.run([str(path), *record['version_args']], capture_output=True,
                                   text=True, timeout=20)
            if check.returncode or check.stdout.strip() != record['version']:
                raise GateError('compiler runner version changed/failed')
        result.append(str(path))
    executable = resolve(profile['executable'])
    if sha256(executable.read_bytes()) != profile['executable_sha256']:
        raise GateError('compiler identity changed')
    return result + [str(executable)]


def compile_bytes(raw, profile):
    flags = tuple(profile['flags'])
    if flags not in (MEASURED_FLAGS + ('-nothumb',), MEASURED_FLAGS + ('-thumb',), INTERWORKING_FLAGS):
        raise GateError('unreviewed MWCC flags; measured ARM/Thumb profile required')
    argv = command(profile)
    version = subprocess.run([*argv, '-version'], capture_output=True, text=True, timeout=20)
    if (version.returncode or version.stdout.strip() != profile['version']
            or version.stderr != profile.get('version_stderr', '')):
        raise GateError('MWCC version probe failed or changed; no automatic fallback')
    with tempfile.TemporaryDirectory(prefix='pvz-mwcc-function-') as td:
        work = Path(td)
        (work / 'candidate.c').write_bytes(raw)
        result = subprocess.run([*argv, '-c', *flags, '-o', str(work / 'candidate.o'),
                                 'candidate.c'], cwd=work, capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise GateError('compiler failure: ' + str(result.returncode) + '\n' + result.stderr[:3000])
        return (work / 'candidate.o').read_bytes(), result.stdout + result.stderr
