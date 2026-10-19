"""Measure isolated compiler output. No masks, register renaming or ROM writes."""
import sys
sys.dont_write_bytecode = True
import argparse
import json
from pathlib import Path
from disasm import decode
from project import GateError, ROOT, REVISION, original, read_json, sha256, validate_universe, load_universe
from wip_support import compile_bytes, extract_text


def compare(target, candidate, mode, address, code_size):
    byte_diff = sum(a != b for a, b in zip(target, candidate)) + abs(len(target) - len(candidate))
    result = {"target_size": len(target), "candidate_size": len(candidate),
              "resolved_byte_differences": byte_diff, "instruction_differences": None,
              "masked_fields": [], "registers_normalized": False,
              "comparator": "unmasked-capstone5-instruction-boundaries-v1",
              "near_threshold": {"instructions": 4, "resolved_bytes": 16}, "tier": "X"}
    if len(target) != len(candidate):
        return result
    left = decode(target[:code_size], address, mode)
    right = decode(candidate[:code_size], address, mode)
    if [(i[0], len(i[1])) for i in left] != [(i[0], len(i[1])) for i in right]:
        result["blocker"] = "instruction boundary/width discrepancy"
        return result
    differences = sum(a[1] != b[1] for a, b in zip(left, right))
    result["instruction_differences"] = differences
    if byte_diff == 0 and differences == 0:
        result["tier"] = "S"
    elif differences <= 4 and byte_diff <= 16:
        result["tier"] = "N"
    return result


def target_bytes(rom_path, fn, root=ROOT):
    data = original(rom_path)
    universe = load_universe(root)
    validate_universe(universe)
    expected = [f for f in universe["functions"] if f["id"] == fn["id"]]
    if len(expected) != 1 or expected[0] != fn or fn.get("size") is None:
        raise GateError("wrong/unbounded target function")
    off = fn["rom_offset"]
    target = data[off:off + fn["size"]]
    if sha256(target) != fn["target_sha256"]:
        raise GateError("wrong target function input")
    return target


def evaluate(source, profile_path, function_id, rom_path, root=ROOT):
    source_bytes = Path(source).read_bytes()
    profile_bytes = Path(profile_path).read_bytes()
    source_hash = sha256(source_bytes)
    profile_hash = sha256(profile_bytes)
    universe = load_universe(root)
    found = [f for f in universe["functions"] if f["id"] == function_id]
    if len(found) != 1:
        raise GateError("unknown/ambiguous function ID")
    fn = found[0]
    target = target_bytes(rom_path, fn, root)
    profile = json.loads(profile_bytes)
    obj, diagnostics = compile_bytes(source_bytes, profile)
    output = extract_text(obj, profile['symbol_values'])
    if (sha256(Path(source).read_bytes()) != source_hash
            or sha256(Path(profile_path).read_bytes()) != profile_hash):
        raise GateError("source/profile changed during compilation; discard result")
    metrics = compare(target, output, fn["mode"], fn["address"], fn["code_size"])
    return {"function": fn, "source_sha256": source_hash,
            "profile_sha256": profile_hash,
            "compiler_profile": profile, "metrics": metrics,
            "diagnostics": diagnostics, "output_sha256": sha256(output)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("function")
    parser.add_argument("--profile", type=Path, required=True)
    parser.add_argument("--rom", type=Path, required=True)
    args = parser.parse_args()
    try:
        result = evaluate(args.source, args.profile, args.function, args.rom)
        print(json.dumps(result, indent=2))
        return 0 if result["metrics"]["tier"] == "S" else 1
    except (GateError, OSError, ValueError, KeyError, ImportError) as exc:
        print("PROBE ERROR: " + str(exc))
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
