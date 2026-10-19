"""Clone the requested public donor sparsely, pin it, and never build it."""
import argparse
from pathlib import Path
import subprocess
from project import ROOT, read_json


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--destination', type=Path, required=True)
    args = parser.parse_args()
    lock = read_json(ROOT / 'docs/donor-lock.json')
    destination = args.destination.resolve()
    if destination.exists():
        raise SystemExit('Refusing existing destination; inspect/preserve it before retrying')
    subprocess.run(['git', 'clone', '--filter=blob:none', '--no-checkout', '--sparse',
                    lock['repository'] + '.git', str(destination)], check=True)
    subprocess.run(['git', '-C', str(destination), 'sparse-checkout', 'set',
                    'Lawn', 'SexyAppFramework', 'Sexy.TodLib'], check=True)
    subprocess.run(['git', '-C', str(destination), 'checkout', '--detach', lock['commit']], check=True)
    actual = subprocess.check_output(['git', '-C', str(destination), 'rev-parse', 'HEAD'], text=True).strip()
    if actual != lock['commit']:
        raise SystemExit('Donor checkout identity mismatch')
    print('Pinned donor clone ready for static review only: ' + str(destination))


if __name__ == '__main__':
    main()
