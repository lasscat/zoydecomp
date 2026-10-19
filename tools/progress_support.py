"""Read and validate saved Track-B evidence without compiling or building anything."""
from pathlib import Path
from project import GateError, ORIGINAL_SHA256, REVISION, ROOT, dual_counters, read_json, sha256, accepted_functions


def behavior_evidence(item, tree):
    """Validate separate sampled evidence; it never changes a comparison tier."""
    evidence = item.get('behavior_validation', {})
    if 'report' not in evidence:
        return None
    path = (tree / evidence['report']).resolve()
    if not path.is_relative_to(tree / 'semantic/behavior'):
        raise GateError('unsafe behavior report')
    report = read_json(path)
    fn = item['function']
    bindings = {'original_sha256': ORIGINAL_SHA256, 'function_id': fn['id'],
                'target_sha256': fn['target_sha256'], 'source_sha256': item['source_sha256'],
                'profile_sha256': item['profile_sha256'],
                'native_compiler_sha256': item['compiler_profile']['executable_sha256']}
    if (sha256(path.read_bytes()) != evidence['report_sha256']
            or any(report.get(k) != v for k, v in bindings.items())
            or report.get('semantic_equivalence_proven') is not False):
        raise GateError('stale/wrong behavior evidence binding')
    for key, name in [('harness_sha256', 'semantic/tools/behavior_check.py'),
                      ('interpreter_sha256', 'semantic/tools/arm_subset.py')]:
        if report.get(key) != sha256((tree / name).read_bytes()):
            raise GateError('stale behavior harness/interpreter')
    cases = report.get('cases', [])
    if (not cases or report.get('passed_cases') != len(cases)
            or any(c.get('full_state_and_guard_bytes_equal') is not True for c in cases)
            or not report.get('observations') or not report.get('assumptions') or not report.get('unknowns')):
        raise GateError('inconsistent or unscoped behavior report')
    return {'function_id': fn['id'], 'passed_cases': len(cases),
            'transition_scenarios': report.get('transition_scenarios', 0),
            'method': report['method'], 'assumptions': report['assumptions'],
            'untested': report['unknowns'], 'equivalence_proven': False}


def saved_progress(manifest_path, universe, manifest_data=None):
    manifest_path = Path(manifest_path).resolve()
    tree = manifest_path.parent.parent
    manifest = read_json(manifest_path) if manifest_data is None else manifest_data
    inventory = manifest.get('inventory', 'functions-v1.json')
    if inventory not in ('functions-v1.json', 'functions-v2.json'):
        raise GateError('unsupported inventory version')
    functions_hash = sha256((ROOT / 'config' / REVISION / inventory).read_bytes())
    if manifest['original_sha256'] != ORIGINAL_SHA256 or manifest['functions_sha256'] != functions_hash:
        raise GateError('stale/wrong semantic baseline')
    for name, digest in manifest['analysis_inputs'].items():
        if sha256(Path(name).read_bytes()) != digest:
            raise GateError('stale analysis dependency: ' + name)
    for name, digest in manifest['tool_hashes'].items():
        if sha256((tree / name).read_bytes()) != digest:
            raise GateError('stale semantic tool: ' + name)
    identities = {f['id']: f for f in universe['functions']}
    b_ids = accepted_functions()
    tiers = {'B': len(b_ids), 'S': 0, 'N': 0, 'X': 0}
    seen, sbytes, sfunctions = set(), 0, 0
    for item in manifest['best']:
        fn = item['function']
        if fn['id'] in seen or identities.get(fn['id']) != fn:
            raise GateError('duplicate/wrong semantic function')
        seen.add(fn['id'])
        for name, digest in ((item['source'], item['source_sha256']),
                             (item['profile_path'], item['profile_sha256'])):
            p = (tree / name).resolve()
            if not p.is_relative_to(tree) or sha256(p.read_bytes()) != digest:
                raise GateError('stale/unsafe saved candidate input: ' + name)
        tier = item['metrics']['tier']
        compiler = item['compiler_profile']
        if sha256(Path(compiler['executable']).read_bytes()) != compiler['executable_sha256']:
            raise GateError('stale compiler executable')
        for runner in compiler.get('runner_chain', []):
            if sha256(Path(runner['executable']).read_bytes()) != runner['executable_sha256']:
                raise GateError('stale compiler runner')
        if tier not in ('S', 'N', 'X'):
            raise GateError('invalid draft tier')
        if tier == 'S' and (item['metrics']['target_size'] != item['metrics']['candidate_size']
                            or item['metrics']['instruction_differences'] != 0
                            or item['metrics']['resolved_byte_differences'] != 0
                            or item['metrics']['masked_fields']):
            raise GateError('inconsistent S metrics')
        tiers[tier] += 1
        if tier == 'S' and fn['id'] not in b_ids:
            sbytes += fn['code_size']
            sfunctions += 1
    counters = dual_counters(universe)
    counters['B_union_S_functions'] += sfunctions
    counters['B_union_S_code_bytes'] += sbytes
    if counters != manifest['counters']:
        raise GateError('semantic counter inconsistency')
    behavior = [value for item in manifest['best'] if (value := behavior_evidence(item, tree))]
    return {'semantic_report': str(manifest_path), 'counters': counters, 'tiers': tiers,
            'behavior': {'tested_functions': len(behavior),
                         'passed_cases': sum(v['passed_cases'] for v in behavior),
                         'evidence': behavior, 'equivalence_proven': False},
            'delta': {'functions': counters['B_union_S_functions'], 'code_bytes': counters['B_union_S_code_bytes'],
                      'code_percentage_points': None if counters['total_code_bytes'] is None else
                      100 * counters['B_union_S_code_bytes'] / counters['total_code_bytes']}}
