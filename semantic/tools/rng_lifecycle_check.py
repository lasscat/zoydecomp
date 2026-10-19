"""Supplemental four-entry RNG oracle. No similarity credit or ROM build."""
import sys
sys.dont_write_bytecode = True
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from project import GateError, ORIGINAL_SHA1, ORIGINAL_SHA256, original, read_json, sha256, write_json
from arm_subset import Region
from arm_call_cluster import ArmCallCluster
from behavior_check import fixed_state

SOURCE = 'semantic/systems/rng_lifecycle.c'
PROFILE = 'semantic/profiles/clang23-arm946-o2.json'
REPORT = ROOT / 'semantic/behavior/rng-lifecycle.json'
FILES = [SOURCE, PROFILE, 'semantic/NOTICE-MT.txt',
         'semantic/tools/rng_lifecycle_check.py', 'semantic/tools/arm_subset.py',
         'semantic/tools/arm_call_cluster.py', 'semantic/tests/test_arm_call_cluster.py',
         'semantic/tools/behavior_check.py', 'tools/project.py',
         'config/BWBE-r0/rom-layout.json', 'config/BWBE-r0/functions-v2.json']
CODE_BASE, CODE_END = 0x02034f40, 0x020350e8
SEED, DEFAULT, MASKED, NEXT = 0x02034f40, 0x02034f94, 0x02034fb0, 0x02034fc0
CALL_EDGES = {0x02034fb4: DEFAULT}
A, B, GLOBAL, STACK, STOP = 0x02280000, 0x02281000, 0x02105dfc, 0x03000000, 0x01000000
SIZE = 64 + 2504 + 64


def bindings():
    return {name: sha256((ROOT / name).read_bytes()) for name in FILES}


def validate_report(report):
    if (report.get('bindings') != bindings() or report.get('original_sha1') != ORIGINAL_SHA1
            or report.get('original_sha256') != ORIGINAL_SHA256
            or report.get('semantic_equivalence_proven') is not False
            or report.get('model_version') != ArmCallCluster.VERSION):
        raise GateError('stale/wrong supplemental RNG behavior bindings')
    cases = report.get('cases', [])
    if (len(cases) != 1263 or report.get('passed_calls') != len(cases)
            or any(not all(case.get(k) is True for k in
                           ('full_states_and_guards_equal', 'guards_unchanged',
                            'original_preserved_registers_sp_equal', 'stack_guards_unchanged',
                            'default_global_unchanged')) for case in cases)
            or not all(report.get('negative_controls', {}).get(k, {}).get('detected') is True
                       for k in ('wrong_return', 'wrong_memory'))):
        raise GateError('inconsistent supplemental RNG cases/negative controls')
    profile = read_json(ROOT / PROFILE)
    if sha256(Path(profile['executable']).read_bytes()) != report.get('native_compiler_sha256'):
        raise GateError('stale supplemental RNG native compiler')
    return {'status': report['status'], 'passed_calls': len(cases),
            'paired_draws': report['paired_draws'], 'equivalence_proven': False}


def check(rom_path):
    before = bindings()
    data = original(rom_path)
    layout = read_json(ROOT / 'config/BWBE-r0/rom-layout.json')
    module = next(row for row in layout['modules'] if row['module'] == 'arm9')
    offset = module['rom_offset'] + CODE_BASE - module['load_address']
    code = data[offset:offset + CODE_END - CODE_BASE]
    if sha256(code) != '9dd917e31e3f1c825ebf8418024dda28dda7a0532e13316b62e910d83fdb399a':
        raise GateError('wrong complete RNG code/pool region')
    inventory = read_json(ROOT / 'config/BWBE-r0/functions-v2.json')['functions']
    targets = {}
    for address, size in [(SEED, 84), (DEFAULT, 28), (MASKED, 16), (NEXT, 296)]:
        start = module['rom_offset'] + address - module['load_address']
        digest = sha256(data[start:start + size])
        if address in (SEED, NEXT):
            fn = next(row for row in inventory if row['id'] == f'arm9:{address:08x}:arm')
            if fn['rom_offset'] != start or fn['size'] != size or fn['target_sha256'] != digest:
                raise GateError('RNG target mapping/hash differs from frozen inventory')
        targets[f'arm9:{address:08x}:arm'] = {
            'address': address, 'size': size, 'rom_offset': start, 'sha256': digest,
            'boundary_status': 'reviewed inventory' if address in (SEED, NEXT) else
                               'behavior-only wrapper interval; no strict inventory credit'}
    word = int.from_bytes(code[0x02034fb4 - CODE_BASE:0x02034fb8 - CODE_BASE], 'little')
    immediate = word & 0xffffff
    if immediate & 0x800000:
        immediate -= 1 << 24
    if word & 0xff000000 != 0xeb000000 or 0x02034fb4 + 8 + immediate * 4 != DEFAULT:
        raise GateError('original BL does not match the declared wrapper edge')

    profile = read_json(ROOT / PROFILE)
    compiler = Path(profile['executable'])
    if sha256(compiler.read_bytes()) != profile['executable_sha256']:
        raise GateError('native compiler differs from pinned profile')
    source = (ROOT / SOURCE).read_bytes()
    harness = source + b'''
_Static_assert(sizeof(unsigned int) == 4, "word width");
_Static_assert(sizeof(struct PvzMtState) == 2504, "DS state layout");
struct PvzMtState *pvz_mt_default_state;
int control_wrong_return(struct PvzMtState *s, unsigned int seed)
{ (void)s; (void)seed; return 0; }
int control_wrong_memory(struct PvzMtState *s, unsigned int seed)
{ int result = pvz_mt_seed(s, seed); ((unsigned char *)s)[-1] ^= 1; return result; }
'''
    flags = ['-shared', '-fPIC', '-O2', '-std=c11', '-ffreestanding', '-fno-builtin']
    with tempfile.TemporaryDirectory(prefix='pvz-rng-lifecycle-') as td:
        work = Path(td)
        (work / 'candidate.c').write_bytes(harness)
        built = subprocess.run([str(compiler), *flags, 'candidate.c', '-o', 'candidate.so'],
                               cwd=work, capture_output=True, text=True, timeout=30)
        if built.returncode:
            raise GateError('native lifecycle compiler failed: ' + built.stderr)
        native_hash = sha256((work / 'candidate.so').read_bytes())
        lib = C.CDLL(str(work / 'candidate.so'))
        names = {SEED: 'pvz_mt_seed', DEFAULT: 'pvz_mt_next_default',
                 MASKED: 'pvz_mt_next_nonnegative', NEXT: 'pvz_mt_next'}
        for entry, name in names.items():
            function = getattr(lib, name)
            function.argtypes = [C.c_void_p, C.c_uint32] if entry == SEED else [C.c_void_p]
            function.restype = C.c_uint32
        for name in ('control_wrong_return', 'control_wrong_memory'):
            getattr(lib, name).argtypes = [C.c_void_p, C.c_uint32]
            getattr(lib, name).restype = C.c_uint32

        buffers = {A: fixed_state(A, SIZE), B: fixed_state(B, SIZE)}
        for base, buffer in buffers.items():
            C.memset(base, 0xa5 if base == A else 0x5a, SIZE)
        global_base = GLOBAL & ~0xfff
        global_page = fixed_state(global_base, 4096)
        C.memset(global_base, 0x69, 4096)
        C.c_uint32.from_address(GLOBAL).value = B + 64
        C.c_void_p.in_dll(lib, 'pvz_mt_default_state').value = B + 64
        global_initial = bytes(global_page)
        guard_bytes = {base: (bytes(buffer[:64]), bytes(buffer[-64:])) for base, buffer in buffers.items()}
        cases = []

        def call(entry, state, seed=None, override=None, record=True):
            snapshots = {base: bytes(buffer) for base, buffer in buffers.items()}
            states = {base: Region(base, bytearray(raw), True) for base, raw in snapshots.items()}
            glob = Region(global_base, bytearray(global_page), True)
            stack = Region(STACK, bytearray([0xcc] * 4096), True)
            cpu = ArmCallCluster([Region(CODE_BASE, bytearray(code), False), *states.values(), glob, stack],
                                CALL_EDGES)
            cpu.r = [0x12340000 + i * 256 for i in range(16)]
            cpu.r[0], cpu.r[1] = state, seed or 0
            cpu.r[13], cpu.r[14], cpu.r[15] = STACK + 4032, STOP, entry
            preserved, sp = cpu.r[4:12], cpu.r[13]
            steps = cpu.run(STOP, limit=200000)
            function = override if override is not None else getattr(lib, names[entry])
            result = function(state, seed) if entry == SEED else function(state)
            if cpu.r[0] != result:
                raise GateError('lifecycle return discrepancy')
            if any(bytes(states[base].data) != bytes(buffer) for base, buffer in buffers.items()):
                raise GateError('lifecycle full-state/guard discrepancy')
            if any((bytes(buffer[:64]), bytes(buffer[-64:])) != guard_bytes[base]
                   for base, buffer in buffers.items()):
                raise GateError('lifecycle guard changed')
            if cpu.r[4:12] != preserved or cpu.r[13] != sp:
                raise GateError('lifecycle original preserved registers/SP discrepancy')
            if stack.data[:64] != bytes([0xcc] * 64) or stack.data[-64:] != bytes([0xcc] * 64):
                raise GateError('lifecycle original stack guard changed')
            if (bytes(glob.data) != global_initial or bytes(global_page) != global_initial
                    or C.c_void_p.in_dll(lib, 'pvz_mt_default_state').value != B + 64):
                raise GateError('lifecycle controlled default global changed')
            active = B if state == 0 else state - 64
            if any(base != active and bytes(buffer) != snapshots[base] for base, buffer in buffers.items()):
                raise GateError('lifecycle unrelated stream changed')
            if record:
                cases.append({'entry': f'0x{entry:08x}', 'state': state, 'seed': seed,
                              'return': int(result), 'original_instructions': steps,
                              'state_and_guard_hashes_before': {hex(b): sha256(v) for b, v in snapshots.items()},
                              'state_and_guard_hashes_after': {hex(b): sha256(bytes(v)) for b, v in buffers.items()},
                              'full_states_and_guards_equal': True, 'guards_unchanged': True,
                              'original_preserved_registers_sp_equal': True,
                              'stack_guards_unchanged': True, 'default_global_unchanged': True})
            return int(result)

        controls = {}
        for label in ('wrong_return', 'wrong_memory'):
            saved = {base: bytes(buffer) for base, buffer in buffers.items()}
            try:
                call(SEED, A + 64, 1, override=getattr(lib, 'control_' + label), record=False)
            except GateError as exc:
                expected = 'return discrepancy' if label == 'wrong_return' else 'full-state/guard discrepancy'
                if expected not in str(exc):
                    raise
                controls[label] = {'detected': True, 'diagnostic': str(exc)}
            else:
                raise GateError('compiled negative control was not detected: ' + label)
            finally:
                for base, raw in saved.items():
                    C.memmove(base, raw, len(raw))

        call(SEED, A + 64, 1)
        call(SEED, A + 64, 0)
        call(SEED, A + 64, 0x2468ace0)
        call(SEED, B + 64, 0x13579bdf)
        call(DEFAULT, 0)
        call(MASKED, B + 64)
        call(SEED, A + 64, 1)
        call(SEED, B + 64, 1)
        high_bit_raw = 0
        for draw in range(626):
            masked = call(MASKED, A + 64)
            raw = call(NEXT, B + 64)
            left, right = bytes(buffers[A]), bytes(buffers[B])
            cursor_a = int.from_bytes(left[68:72], 'little') - (A + 72)
            cursor_b = int.from_bytes(right[68:72], 'little') - (B + 72)
            if (masked != raw & 0x7fffffff or left[64:68] != right[64:68]
                    or left[72:64 + 2504] != right[72:64 + 2504] or cursor_a != cursor_b):
                raise GateError('paired raw/masked stream relation discrepancy')
            high_bit_raw += bool(raw & 0x80000000)
        call(SEED, A + 64, 0)
        call(SEED, B + 64, 0x2468ace0)
        call(NEXT, B + 64)

    if bindings() != before or sha256(compiler.read_bytes()) != profile['executable_sha256']:
        raise GateError('lifecycle inputs changed during behavior run')
    report = {'schema': 1, 'status': 'passed sampled connected lifecycle; no equivalence proof',
              'original_sha1': ORIGINAL_SHA1, 'original_sha256': ORIGINAL_SHA256,
              'bindings': before, 'targets': targets, 'code_region_sha256': sha256(code),
              'model_version': ArmCallCluster.VERSION, 'call_edges': {'0x02034fb4': '0x02034f94'},
              'native_compiler_sha256': profile['executable_sha256'], 'native_flags': flags,
              'native_harness_sha256': sha256(harness), 'native_object_sha256': native_hash,
              'cases': cases, 'passed_calls': len(cases), 'paired_draws': 626,
              'raw_high_bit_set_draws': high_bit_raw, 'negative_controls': controls,
              'strict_status': 'blocked: seed/next compiler nonmatches; default helper tail branch outside scope',
              'similarity_status': 'not measured for this restatement; canonical seed/next remain X',
              'assumptions': ['32-bit unsigned int and 2504-byte layout asserted at native compilation',
                              'fixed low host mappings preserve exact DS cursor pointer values',
                              'accessible nonaliasing code/state/stack and controlled default pointer',
                              'restricted base model plus whitelisted BL extension; no hardware validation'],
              'unknowns': ['real null-default initialization/owner and reachability',
                           'all other seeds/states and invalid cursor/counter inputs',
                           'hardware timing/interrupts, native-vs-ARM ABI, whole-game behavior'],
              'semantic_equivalence_proven': False}
    validate_report(report)
    write_json(REPORT, report)
    print(validate_report(report))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--status', action='store_true')
    args = parser.parse_args()
    try:
        if args.status:
            print(validate_report(read_json(REPORT)))
        elif args.rom is None:
            raise GateError('--rom must explicitly identify the legally supplied original')
        else:
            check(args.rom)
        return 0
    except (GateError, OSError, ValueError, RuntimeError, subprocess.SubprocessError) as exc:
        print('RNG LIFECYCLE CHECK FAILED: ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
