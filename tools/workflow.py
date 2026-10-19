"""Read-only status; explicit, serialized baseline preparation/build/verification."""
import sys
sys.dont_write_bytecode = True
import argparse
import json
from pathlib import Path
import subprocess
from project import GateError, ROOT, REVISION, ORIGINAL_SHA1, ORIGINAL_SHA256
from project import dual_counters, git, isolation, pipeline_lock, read_json, sha256, write_json
from project import materials_digest, load_universe, accepted_functions
import rom


def inputs_digest():
    return materials_digest()


def verification_current(saved):
    output = ROOT / 'build' / REVISION / 'pvz.nds'
    return (saved.get('inputs_digest') == inputs_digest()
            and saved.get('sha1') == ORIGINAL_SHA1 and saved.get('sha256') == ORIGINAL_SHA256
            and saved.get('full_byte_compare') is True and saved.get('output') == str(output)
            and output.is_file() and sha256(output.read_bytes()) == ORIGINAL_SHA256)


def status(semantic_report=None):
    universe = load_universe()
    try:
        head = git("rev-parse", "--verify", "HEAD")
    except subprocess.CalledProcessError:
        head = "unborn"
    result = {"branch": git("branch", "--show-current"), "head": head,
              "target": REVISION, "original_sha1": ORIGINAL_SHA1,
              "counters": dual_counters(universe), "known_inventory_entries": len(universe["functions"]),
              "tiers": {"B": len(accepted_functions()), "S": 0, "N": 0, "X": 0},
              "behavior": {"tested_functions": None, "passed_cases": None,
                           "status": "not loaded; pass --semantic-report; behavior is separate evidence"},
              "warning": "Function denominator incomplete; retained binary receives no C credit"}
    if semantic_report is not None:
        from progress_support import saved_progress
        result.update(saved_progress(semantic_report, universe))
    else:
        result['semantic_report'] = 'not loaded; zero is Track-A saved S credit only; pass --semantic-report for Track B'
    report = ROOT / "build" / REVISION / "verification.json"
    if report.exists():
        saved = read_json(report)
        result["saved_verification"] = saved
        result["verification_inputs_current"] = verification_current(saved)
    else:
        result["saved_verification"] = None
    print(json.dumps(result, indent=2))


def format_paths(paths):
    for name in paths:
        p = ROOT / name
        if not p.is_file() or p.is_symlink() or not p.resolve().is_relative_to(ROOT):
            raise GateError("explicit regular repository file required: " + name)
        if any(part in ("rom", "extract", "build", "reference", ".git", "semantic") for part in Path(name).parts):
            raise GateError("forbidden integration path: " + name)
        if p.suffix in (".bin", ".nds", ".o", ".elf", ".exe", ".dll", ".srl"):
            raise GateError("binary integration path forbidden")
        raw = p.read_bytes()
        try:
            text = raw.decode("utf-8")
        except UnicodeDecodeError as exc:
            raise GateError("binary integration content forbidden") from exc
        formatted = "\n".join(line.rstrip() for line in text.splitlines()).rstrip("\n") + "\n"
        if p.suffix == '.c':
            tool = read_json(ROOT / 'config' / REVISION / 'formatter.json')
            executable = Path(tool['executable'])
            if sha256(executable.read_bytes()) != tool['executable_sha256']:
                raise GateError('formatter identity changed')
            formatted = subprocess.check_output([str(executable), '--style=file', str(p)],
                                                cwd=ROOT, text=True)
        if raw != formatted.encode():
            p.write_text(formatted)
            raise GateError("formatting changed " + name + "; review and rerun finish")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("status", "prepare", "build", "verify", "finish", "integrate"))
    parser.add_argument("paths", nargs="*")
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--semantic-report", type=Path, help="explicit saved Track-B manifest, status only")
    args = parser.parse_args()
    try:
        if args.command == "status":
            status(args.semantic_report)
            return 0
        if args.command in ("prepare", "verify", "finish", "integrate") and args.rom is None:
            raise GateError("--rom must explicitly identify the legally supplied original")
        with pipeline_lock():
            isolation()
            receipt_path = 'config/' + REVISION + '/accepted.json'
            prior = accepted_functions(require_current=False)
            if args.command in ("finish", "integrate"):
                if not args.paths:
                    raise GateError("finish requires explicit file paths; never stage a directory")
                format_paths(args.paths)
                from link_backend import declaration
                configured = {row['id'] for row in declaration()['functions']}
                if configured != prior and receipt_path not in args.paths:
                    raise GateError('acceptance requires explicit accepted.json path')
                subprocess.run(["python3", "-B", "-m", "unittest", "discover", "-s", "tools/tests", "-v"],
                               cwd=ROOT, check=True)
            if args.command == "prepare":
                rom.prepare(args.rom)
                print("PREPARED original components; no build was started")
            elif args.command == "build":
                print("BUILT baseline " + str(rom.build()))
            else:
                before = inputs_digest()
                output = rom.verify(args.rom)
                if before != inputs_digest():
                    raise GateError('strict inputs changed during full build/verification')
                from link_backend import declaration
                accepted = ({row['id'] for row in declaration()['functions']}
                            if args.command in ('finish', 'integrate') else prior)
                if accepted:
                    write_json(ROOT / receipt_path,
                               {'schema': 1, 'original_sha1': ORIGINAL_SHA1,
                                'original_sha256': ORIGINAL_SHA256, 'full_byte_compare': True,
                                'inputs_digest': before, 'functions': sorted(accepted)})
                write_json(ROOT / "build" / REVISION / "verification.json",
                           {"kind": "whole-module C link and retained-component repack", "sha1": ORIGINAL_SHA1,
                            "sha256": ORIGINAL_SHA256, "full_byte_compare": True,
                            "inputs_digest": before, "output": str(output), "B_functions": len(accepted)})
                print("VERIFY PASSED: complete ROM equals immutable original; accepted C: " + str(len(accepted)))
                if args.command in ("finish", "integrate"):
                    snapshots = {p: (ROOT / p).read_bytes() for p in args.paths}
                    subprocess.run(["git", "add", "--", *args.paths], cwd=ROOT, check=True)
                    for p, data in snapshots.items():
                        staged = subprocess.check_output(['git', 'show', ':' + p], cwd=ROOT)
                        if staged != data or (ROOT / p).read_bytes() != data:
                            raise GateError('file changed during explicit staging: ' + p)
                    if before != inputs_digest() or not verification_current(read_json(
                            ROOT / 'build' / REVISION / 'verification.json')):
                        raise GateError('verification became stale during staging; do not commit')
                    print("STAGED explicit paths only; no commit/push performed")
        return 0
    except (GateError, OSError, ValueError, KeyError, subprocess.CalledProcessError) as exc:
        print("GATE FAILED: " + str(exc))
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
