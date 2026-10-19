"""Sampled MT seed differential check. Does not assign matching/equivalence credit."""
import sys
sys.dont_write_bytecode = True
import argparse
import ctypes as C
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from project import GateError, ORIGINAL_SHA256, read_json, sha256, write_json, load_universe
from probe_compiler import target_bytes
from semantic_progress import validate_candidate
from arm_subset import Arm, Region


def check(rom_path):
    candidate = read_json(ROOT / 'semantic/candidates.json')['candidates'][0]
    source, profile_path = validate_candidate(candidate, validate_behavior=False)
    fn = next(f for f in load_universe()['functions']
              if f['id'] == candidate['function_id'])
    target = target_bytes(rom_path, fn, ROOT)
    profile = read_json(profile_path)
    # Native C has a fixed 32-bit address placeholder, preserving +0/+4/+8 layout.
    source_before = source.read_bytes()
    if sha256(source_before) != candidate['source_sha256']:
        raise GateError('source changed before behavior compilation')
    harness = source_before.decode('ascii') + '\n_Static_assert(sizeof(struct PvzMtState) == 2504, "state layout");\n'
    seeds = [0, 1, 4357, 0xffffffff, 0x80000000, 0x7fffffff, 2, 623]
    seeds += [((i + 1) * 0x9e3779b9) & 0xffffffff for i in range(24)]
    sequences = [[seed] for seed in seeds] + [[1, 0], [4357, 1], [0xffffffff, 0x80000000], [623, 623, 0]]
    with tempfile.TemporaryDirectory(prefix='pvz-behavior-') as td:
        work = Path(td)
        (work / 'candidate.c').write_text(harness)
        flags = ['-shared', '-fPIC', '-O2', '-std=c11', '-ffreestanding', '-fno-builtin']
        result = subprocess.run([profile['executable'], *flags, 'candidate.c', '-o', 'candidate.so'],
                                cwd=work, capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise GateError('native behavior build failed: ' + result.stderr)
        library = C.CDLL(str(work / 'candidate.so'))
        function = library.pvz_mt_seed
        function.argtypes, function.restype = [C.c_void_p, C.c_uint32], C.c_int
        cases = []
        for index, sequence in enumerate(sequences):
            initial = bytes((i * 17 + index * 29) & 255 for i in range(64 + 2504 + 64))
            state = Region(0x02280000, bytearray(initial), True)
            native = (C.c_ubyte * len(initial)).from_buffer_copy(initial)
            for step, seed in enumerate(sequence):
                before = sha256(bytes(state.data))
                stack = Region(0x03000000, bytearray(4096), True)
                cpu = Arm([Region(fn['address'], bytearray(target), False), state, stack])
                cpu.r = [(0x12340000 + i * 0x100) for i in range(16)]
                cpu.r[0], cpu.r[1] = state.base + 64, seed
                cpu.r[13], cpu.r[14], cpu.r[15] = stack.base + 4080, 0x01000000, fn['address']
                preserved, sp = cpu.r[4:12], cpu.r[13]
                steps = cpu.run(cpu.r[14])
                if cpu.r[4:12] != preserved or cpu.r[13] != sp:
                    raise GateError('original callee-saved/SP discrepancy')
                native_return = function(C.byref(native, 64), seed)
                if cpu.r[0] != native_return or bytes(state.data) != bytes(native):
                    raise GateError(f'behavior discrepancy in scenario {index}, step {step}, seed {seed:#x}')
                if bytes(state.data[:64]) != initial[:64] or bytes(state.data[-64:]) != initial[-64:]:
                    raise GateError('guard bytes changed')
                cases.append({'scenario': index, 'step': step, 'seed': seed,
                              'transition_sequence': len(sequence) > 1,
                              'initial_state_and_guards_sha256': before,
                              'final_state_and_guards_sha256': sha256(bytes(state.data)),
                              'return_value': native_return, 'original_instructions': steps,
                              'full_state_and_guard_bytes_equal': True})
    if source.read_bytes() != source_before:
        raise GateError('source changed during behavior test; discard evidence')
    report = {'schema': 1, 'function_id': fn['id'], 'original_sha256': ORIGINAL_SHA256,
              'target_sha256': fn['target_sha256'], 'source_sha256': candidate['source_sha256'],
              'profile_sha256': candidate['profile_sha256'], 'native_compiler': profile['executable'],
              'native_compiler_sha256': profile['executable_sha256'], 'native_flags': flags,
              'harness_sha256': sha256(Path(__file__).read_bytes()),
              'interpreter_sha256': sha256((ROOT / 'semantic/tools/arm_subset.py').read_bytes()),
              'cases': cases, 'passed_cases': len(cases), 'scenario_count': len(sequences),
              'transition_scenarios': 4, 'semantic_equivalence_proven': False,
              'method': 'original ROM instructions in restricted ARM interpreter versus host-compiled saved C',
              'observations': ['return value', '2504-byte state', '128 surrounding guard bytes',
                               'original callee-saved r4-r11 and restored SP',
                               'zero-seed rejection after initialization, reseeding, repeated seeds'],
              'assumptions': ['word-aligned accessible nonaliasing state/code/stack',
                              'restricted ARM model implements exercised instructions correctly',
                              'host unsigned int is 32-bit; layout static assertion passed'],
              'unknowns': ['all untested seeds and initial states', 'hardware timing and interrupts',
                           'real DS execution', 'whole-game behavior', 'formal equivalence',
                           'native versus ARM ABI not directly compared']}
    write_json(ROOT / 'semantic/behavior/mt_seed.json', report)
    print(f'BEHAVIOR SAMPLES PASSED: {len(cases)}; equivalence proven: false')


def compare_predicate_case(fn, target, native_function, value):
    """One original-instruction/native-C check; discrepancies are hard failures."""
    initial = bytearray((i * 17 + 29) & 255 for i in range(64 + 0x60 + 64))
    initial[64 + 0x5c:64 + 0x60] = value.to_bytes(4, 'little')
    state = Region(0x02280000, bytearray(initial), True)
    stack = Region(0x03000000, bytearray(4096), True)
    cpu = Arm([Region(fn['address'], bytearray(target), False), state, stack])
    cpu.r = [(0x12340000 + i * 0x100) for i in range(16)]
    cpu.r[0] = state.base + 64
    cpu.r[13], cpu.r[14], cpu.r[15] = stack.base + 4080, 0x01000000, fn['address']
    preserved, sp = cpu.r[4:12], cpu.r[13]
    steps = cpu.run(cpu.r[14], limit=256)
    native = (C.c_ubyte * len(initial)).from_buffer_copy(initial)
    if (C.addressof(native) + 64) % 4:
        raise GateError('native owner is not word aligned')
    native_return = native_function(C.byref(native, 64))
    if cpu.r[0] != native_return:
        raise GateError(f'predicate return discrepancy for field {value:#x}')
    if bytes(state.data) != bytes(native) or bytes(state.data) != bytes(initial):
        raise GateError(f'predicate memory/guard discrepancy for field {value:#x}')
    if cpu.r[4:12] != preserved or cpu.r[13] != sp:
        raise GateError('predicate callee-saved/SP discrepancy')
    return {'value': value, 'return_value': native_return, 'original_instructions': steps,
            'full_state_and_guard_bytes_equal': True, 'owner_and_guards_unchanged': True}


def check_predicates(rom_path):
    ids = ['arm9:02068fd8:arm', 'arm9:02068ff0:arm',
           'arm9:02069008:arm', 'arm9:0206901c:arm']
    items = [next(item for item in read_json(ROOT / 'semantic/candidates.json')['candidates']
                  if item['function_id'] == identity) for identity in ids]
    universe = {fn['id']: fn for fn in load_universe()['functions']}
    sources, profiles, targets = [], [], []
    for item in items:
        source, path = validate_candidate(item, validate_behavior=False)
        sources.append(source.read_bytes())
        profiles.append(read_json(path))
        targets.append(target_bytes(rom_path, universe[item['function_id']], ROOT))
    if len({profile['executable_sha256'] for profile in profiles}) != 1:
        raise GateError('predicate native compiler profiles differ; review harness')
    values = sorted(set(list(range(36)) + [0xfffffffc, 0xfffffffd, 0xfffffffe,
                          0xffffffff, 0x7fffffff, 0x80000000, 0x80000001] +
                         [((i + 1) * 0x9e3779b9) & 0xffffffff for i in range(256)]))
    transitions = [0, 1, 3, 4, 6, 7, 24, 25, 28, 29, 30, 31, 0xffffffff, 0]
    flags = ['-shared', '-fPIC', '-O2', '-std=c11', '-ffreestanding', '-fno-builtin']
    reports = []
    with tempfile.TemporaryDirectory(prefix='pvz-predicate-behavior-') as td:
        work = Path(td)
        harness = b'\n'.join(sources) + b'\n_Static_assert(sizeof(unsigned int) == 4, "word width");\n'
        (work / 'candidate.c').write_bytes(harness)
        result = subprocess.run([profiles[0]['executable'], *flags, 'candidate.c', '-o', 'candidate.so'],
                                cwd=work, capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise GateError('predicate native build failed: ' + result.stderr)
        library = C.CDLL(str(work / 'candidate.so'))
        for item, raw, profile, target in zip(items, sources, profiles, targets):
            identity = item['function_id']
            address = identity.split(':')[1]
            symbol = 'pvz_' + address + ('_test_unknown_word_equal' if address == '02069008'
                                         else '_test_unknown_word_range')
            function = getattr(library, symbol)
            function.argtypes, function.restype = [C.c_void_p], C.c_int
            cases = [compare_predicate_case(universe[identity], target, function, value)
                     for value in values]
            # The functions are read-only predicates. These ordered field-value
            # changes are controlled inputs, not inferred gameplay transitions.
            for step, value in enumerate(transitions):
                case = compare_predicate_case(universe[identity], target, function, value)
                case.update(controlled_field_transition_step=step)
                cases.append(case)
            report = {'schema': 1, 'function_id': identity, 'original_sha256': ORIGINAL_SHA256,
                      'target_sha256': universe[identity]['target_sha256'],
                      'source_sha256': item['source_sha256'], 'profile_sha256': item['profile_sha256'],
                      'native_compiler': profile['executable'],
                      'native_compiler_sha256': profile['executable_sha256'], 'native_flags': flags,
                      'harness_sha256': sha256(Path(__file__).read_bytes()),
                      'interpreter_sha256': sha256((ROOT / 'semantic/tools/arm_subset.py').read_bytes()),
                      'cases': cases, 'passed_cases': len(cases), 'transition_scenarios': 0,
                      'controlled_field_value_sequence': transitions,
                      'method': 'original ROM instructions in restricted ARM interpreter versus host-compiled saved C',
                      'observations': ['boolean return', 'entire 96-byte owner and 128 guard bytes unchanged',
                                       'original preserved r4-r11 and SP'],
                      'assumptions': ['aligned accessible 96-byte owner; 32-bit unsigned int',
                                      'single-threaded stable field at +0x5c; no MMIO or interrupts',
                                      'restricted ARM model implements exercised instructions correctly'],
                      'unknowns': ['owner identity, valid gameplay states and writes to +0x5c',
                                   'all other field values and memory states', 'actual gameplay transitions',
                                   'real DS hardware, timing, native versus ARM ABI and whole-game effects',
                                   'volatile access reflects a source hypothesis, not established source qualification',
                                   'formal equivalence'], 'semantic_equivalence_proven': False}
            if sha256((ROOT / item['source']).read_bytes()) != item['source_sha256']:
                raise GateError('predicate source changed during behavior check')
            reports.append((ROOT / 'semantic/behavior' / ('predicate-' + address + '.json'), report))
    for path, report in reports:
        write_json(path, report)
    print(f'PREDICATE SAMPLES PASSED: {len(reports)} functions, {sum(len(r["cases"]) for _, r in reports)} calls; equivalence proven: false')


def fixed_state(address, size):
    """Map a state buffer at the exact ARM address so stored pointers compare."""
    libc = C.CDLL('libc.so.6', use_errno=True)
    libc.mmap.restype = C.c_void_p
    libc.mmap.argtypes = [C.c_void_p, C.c_size_t, C.c_int, C.c_int, C.c_int, C.c_long]
    prot = 1 | 2                       # PROT_READ | PROT_WRITE
    flags = 2 | 0x20 | 0x100000        # MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE
    got = libc.mmap(address, size, prot, flags, -1, 0)
    if got in (None, 0) or got == 0xffffffffffffffff:
        raise GateError('fixed-address RNG state mapping failed')
    return (C.c_ubyte * size).from_address(address)


def compare_next_sequence(state_base, buffer, seed_fn, seed_target, next_fn, next_target,
                          native_seed, native_next, steps, initial, scenario_index):
    """One seed/next scenario on identical ARM and native state; hard-fails on any difference."""
    region = Region(state_base, bytearray(initial), True)
    stack = Region(0x03000000, bytearray(4096), True)
    C.memmove(state_base, initial, len(initial))
    cases = []

    def run_arm(function, target, argument):
        cpu = Arm([Region(function['address'], bytearray(target), False), region, stack])
        cpu.r = [(0x12340000 + i * 0x100) for i in range(16)]
        cpu.r[0], cpu.r[1] = state_base + 64, argument
        cpu.r[13], cpu.r[14], cpu.r[15] = stack.base + 4080, 0x01000000, function['address']
        preserved, sp = cpu.r[4:12], cpu.r[13]
        count = cpu.run(cpu.r[14], limit=200000)
        if cpu.r[4:12] != preserved or cpu.r[13] != sp:
            raise GateError('original callee-saved/SP discrepancy')
        return cpu.r[0], count

    for step_index, step in enumerate(steps):
        remaining_before = int.from_bytes(bytes(region.data[64:68]), 'little')
        if step[0] == 'seed':
            arm_return, count = run_arm(seed_fn, seed_target, step[1])
            native_return = native_seed(C.c_void_p(state_base + 64), step[1])
            if arm_return != native_return or bytes(region.data) != bytes(buffer):
                raise GateError(f'RNG seed discrepancy scenario {scenario_index} step {step_index}')
            remaining_before = None
        else:
            arm_return, count = run_arm(next_fn, next_target, 0)
            native_return = native_next(C.c_void_p(state_base + 64))
            if arm_return != native_return:
                raise GateError(f'mt_next return discrepancy scenario {scenario_index} step {step_index}')
            if bytes(region.data) != bytes(buffer):
                raise GateError(f'mt_next memory/guard discrepancy scenario {scenario_index} step {step_index}')
        if bytes(region.data[:64]) != initial[:64] or bytes(region.data[-64:]) != initial[-64:]:
            raise GateError('RNG guard bytes changed')
        cases.append({'scenario': scenario_index, 'step': step_index, 'kind': step[0],
                      'seed': step[1] if step[0] == 'seed' else None,
                      'remaining_before': remaining_before, 'reloaded': remaining_before == 1,
                      'return_value': native_return, 'original_instructions': count,
                      'final_state_and_guard_sha256': sha256(bytes(region.data)),
                      'full_state_and_guard_bytes_equal': True})
    return cases


def check_next(rom_path):
    items = {item['function_id']: item for item in read_json(ROOT / 'semantic/candidates.json')['candidates']}
    seed_item = items['arm9:02034f40:arm']
    next_item = items['arm9:02034fc0:arm']
    seed_source, seed_profile_path = validate_candidate(seed_item, validate_behavior=False)
    next_source, next_profile_path = validate_candidate(next_item, validate_behavior=False)
    seed_profile = read_json(seed_profile_path)
    next_profile = read_json(next_profile_path)
    if seed_profile['executable_sha256'] != next_profile['executable_sha256']:
        raise GateError('RNG native compiler profiles differ; review harness')
    universe = {fn['id']: fn for fn in load_universe()['functions']}
    seed_fn, next_fn = universe['arm9:02034f40:arm'], universe['arm9:02034fc0:arm']
    seed_target = target_bytes(rom_path, seed_fn, ROOT)
    next_target = target_bytes(rom_path, next_fn, ROOT)
    seed_before, next_before = seed_source.read_bytes(), next_source.read_bytes()
    # One translation unit: the seed draft owns the struct, the next draft reuses it.
    harness = (b'#define PVZ_MT_STATE_DEFINED\n' + seed_before + b'\n' + next_before
               + b'\n_Static_assert(sizeof(struct PvzMtState) == 2504, "state layout");\n')
    flags = ['-shared', '-fPIC', '-O2', '-std=c11', '-ffreestanding', '-fno-builtin']
    size = 64 + 2504 + 64
    scenarios = []
    for seed in (1, 4357, 0xffffffff, 0x80000000, 0x12345678):
        count = 626 if seed == 1 else 4
        scenarios.append({'name': f'seed {seed:#x} then {count} next',
                          'steps': [('seed', seed)] + [('next',)] * count})
    scenarios.append({'name': 'reseed transition',
                      'steps': [('seed', 0x11111111)] + [('next',)] * 3
                               + [('seed', 0x22222222)] + [('next',)] * 3})
    with tempfile.TemporaryDirectory(prefix='pvz-rng-behavior-') as td:
        work = Path(td)
        (work / 'candidate.c').write_bytes(harness)
        result = subprocess.run([next_profile['executable'], *flags, 'candidate.c', '-o', 'candidate.so'],
                                cwd=work, capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise GateError('RNG native behavior build failed: ' + result.stderr)
        library = C.CDLL(str(work / 'candidate.so'))
        native_seed, native_next = library.pvz_mt_seed, library.pvz_mt_next
        native_seed.argtypes, native_seed.restype = [C.c_void_p, C.c_uint32], C.c_int
        native_next.argtypes, native_next.restype = [C.c_void_p], C.c_uint32
        buffer = fixed_state(0x02280000, size)
        cases = []
        for index, scenario in enumerate(scenarios):
            initial = bytes((i * 17 + index * 29) & 255 for i in range(size))
            cases.extend(compare_next_sequence(0x02280000, buffer, seed_fn, seed_target, next_fn,
                                               next_target, native_seed, native_next,
                                               scenario['steps'], initial, index))
    if seed_source.read_bytes() != seed_before or next_source.read_bytes() != next_before:
        raise GateError('RNG source changed during behavior check; discard evidence')
    report = {'schema': 1, 'function_id': next_fn['id'], 'original_sha256': ORIGINAL_SHA256,
              'target_sha256': next_fn['target_sha256'], 'source_sha256': next_item['source_sha256'],
              'profile_sha256': next_item['profile_sha256'], 'native_compiler': next_profile['executable'],
              'native_compiler_sha256': next_profile['executable_sha256'], 'native_flags': flags,
              'harness_sha256': sha256(Path(__file__).read_bytes()),
              'interpreter_sha256': sha256((ROOT / 'semantic/tools/arm_subset.py').read_bytes()),
              'cases': cases, 'passed_cases': len(cases), 'scenario_count': len(scenarios),
              'transition_scenarios': len(scenarios),
              'state_base': 0x02280000, 'state_size': 2504,
              'method': 'original ROM instructions in restricted ARM interpreter versus host-compiled saved C',
              'observations': ['seed return and full state', 'mt_next 32-bit return and full state',
                               'two complete twist reloads inside one scenario',
                               'state stored at its real ARM address so the +4 cursor compares byte-exactly',
                               'original callee-saved r4-r11 and restored SP', '128 surrounding guard bytes'],
              'assumptions': ['word-aligned accessible nonaliasing state/code/stack',
                              'host unsigned int is 32-bit and the struct is 2504 bytes',
                              'MAP_FIXED_NOREPLACE gives the host state the same address as the ARM run',
                              'single-threaded; restricted ARM model implements exercised instructions'],
              'unknowns': ['all untested seeds, initial states and reload counts', 'hardware timing and interrupts',
                           'real DS execution', 'whole-game determinism', 'per-object vs global state ownership',
                           'native versus ARM ABI not directly compared', 'formal equivalence'],
              'semantic_equivalence_proven': False}
    write_json(ROOT / 'semantic/behavior/mt_next.json', report)
    print(f'RNG SAMPLES PASSED: {len(cases)} calls across {len(scenarios)} scenarios; equivalence proven: false')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, required=True)
    parser.add_argument('--system', choices=('seed', 'predicates', 'next', 'all'), default='seed')
    args = parser.parse_args()
    try:
        if args.system in ('seed', 'all'):
            check(args.rom)
        if args.system in ('predicates', 'all'):
            check_predicates(args.rom)
        if args.system in ('next', 'all'):
            check_next(args.rom)
        return 0
    except (ValueError, OSError, KeyError, subprocess.SubprocessError) as exc:
        print('BEHAVIOR CHECK ERROR: ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
