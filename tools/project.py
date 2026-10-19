"""Immutable identity and shared fail-closed utilities. Standard library only."""
import contextlib
import fcntl
import hashlib
import json
import os
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
REVISION = "BWBE-r0"
ORIGINAL_SHA1 = "fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b"
ORIGINAL_SHA256 = "43dfad7bcaea611a770034919d3fbf77c0ffe41b81483a0eec7774d7c5c418ad"
ORIGINAL_SIZE = 67108864


class GateError(ValueError):
    pass


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def read_json(path):
    return json.loads(Path(path).read_text())


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + ".tmp")
    tmp.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")
    tmp.replace(path)


def original(path):
    data = Path(path).read_bytes()
    if (len(data) != ORIGINAL_SIZE or hashlib.sha1(data).hexdigest() != ORIGINAL_SHA1
            or sha256(data) != ORIGINAL_SHA256):
        raise GateError("wrong ROM identity; immutable original hashes must never be changed")
    if data[12:16] != b"BWBE" or data[30] != 0:
        raise GateError("wrong target/revision")
    return data


def git(*args, root=ROOT):
    return subprocess.check_output(["git", "-C", str(root), *args], text=True).strip()


def strict_only(root=ROOT):
    if git("branch", "--show-current", root=root) != "decomp/strict":
        raise GateError("only the Track-A decomp/strict worktree may run this command")
    entries = git("worktree", "list", "--porcelain", root=root).split("\n\n")
    owners = [e.splitlines()[0][9:] for e in entries
              if "branch refs/heads/decomp/strict" in e.splitlines()]
    if owners != [str(root.resolve())]:
        raise GateError("strict worktree ownership is ambiguous")


@contextlib.contextmanager
def pipeline_lock(root=ROOT):
    strict_only(root)
    common = Path(git("rev-parse", "--git-common-dir", root=root))
    if not common.is_absolute():
        common = root / common
    # Stable inode in the common Git directory, never unlink a live lock.
    with (common / "pvz-pipeline.lock").open("a+") as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as exc:
            raise GateError("another strict writer owns the pipeline; wait, never delete its lock") from exc
        lock.seek(0)
        lock.truncate()
        lock.write(str(os.getpid()) + "\n")
        lock.flush()
        try:
            yield
        finally:
            fcntl.flock(lock, fcntl.LOCK_UN)


def validate_universe(universe):
    seen, intervals = set(), {}
    for fn in universe["functions"]:
        key = (fn["module"], fn["address"], fn["mode"])
        if key in seen:
            raise GateError("duplicate function credit (aliases share one identity)")
        seen.add(key)
        if fn["mode"] not in ("arm", "thumb") or fn["address"] % (4 if fn["mode"] == "arm" else 2):
            raise GateError("invalid address/mode")
        if fn.get("size") is not None:
            if fn["size"] <= 0 or not 0 < fn["code_size"] <= fn["size"]:
                raise GateError("invalid sized code extent")
            group = intervals.setdefault(fn["module"], [])
            a, b = fn["address"], fn["address"] + fn["size"]
            if any(a < y and x < b for x, y in group):
                raise GateError("overlapping function credit")
            group.append((a, b))
    return seen


def isolation(root=ROOT):
    if (root / "semantic").exists():
        raise GateError("semantic/ must not exist on Track A")
    for directory in ("src", "include", "config", "tools"):
        for p in (root / directory).rglob("*"):
            if p.is_symlink():
                raise GateError("symlink in strict build inputs")
            if directory != "tools" and p.is_file() and b"semantic" in p.read_bytes().lower():
                raise GateError("semantic reference in strict source/config: " + str(p))
    from link_backend import validate_declaration
    validate_declaration(root)


def load_universe(root=ROOT):
    from link_backend import declaration
    return read_json(root / "config" / REVISION / declaration(root)["inventory"])


def materials_digest(root=ROOT):
    files = []
    for name in ("tools", "src", "include", "config", "docs/profiles"):
        for p in sorted((root / name).rglob("*")):
            if (p.is_file() and not any(x in p.parts for x in ("__pycache__", "bin"))
                    and p != root / "config" / REVISION / "accepted.json"):
                files.append((str(p.relative_to(root)), sha256(p.read_bytes())))
    if (root / '.clang-format').exists():
        files.append(('.clang-format', sha256((root / '.clang-format').read_bytes())))
    return sha256(json.dumps(files).encode())


def accepted_functions(root=ROOT, require_current=True):
    receipt = read_json(root / "config" / REVISION / "accepted.json")
    ids = receipt['functions']
    if not ids:
        return set()
    from link_backend import validate_declaration
    plan, _ = validate_declaration(root)
    configured = {row['id'] for row in plan['functions']}
    if (receipt.get('schema') != 1 or receipt.get('original_sha1') != ORIGINAL_SHA1
            or receipt.get('original_sha256') != ORIGINAL_SHA256
            or receipt.get('full_byte_compare') is not True
            or len(ids) != len(set(ids)) or not set(ids) <= configured):
        raise GateError('invalid strict acceptance receipt')
    if require_current and receipt.get('inputs_digest') != materials_digest(root):
        raise GateError('strict acceptance receipt is stale; run strict verification')
    return set(ids)


def dual_counters(universe, root=ROOT):
    validate_universe(universe)
    complete = universe["complete"]
    accepted = accepted_functions(root)
    by_id = {f['id']: f for f in universe['functions']}
    if not accepted <= by_id.keys():
        raise GateError('accepted function absent from frozen inventory')
    code_bytes = sum(by_id[key]['code_size'] for key in accepted)
    return {"B_functions": len(accepted), "B_code_bytes": code_bytes,
            "B_union_S_functions": len(accepted), "B_union_S_code_bytes": code_bytes,
            "total_functions": len(universe["functions"]) if complete else None,
            "total_code_bytes": sum(f["code_size"] for f in universe["functions"]
                                    if f.get("size") is not None) if complete else None,
            "denominator_status": "complete" if complete else "incomplete; percentages unavailable"}
