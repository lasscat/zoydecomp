"""Hash-bound candidate bank. Local evidence only; never builds a ROM or accepts B."""
import sys
sys.dont_write_bytecode = True
import argparse
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from project import (GateError, ORIGINAL_SHA256, REVISION, dual_counters, git,
                     original, read_json, sha256, write_json, load_universe, accepted_functions)
from probe_compiler import evaluate
from progress_support import saved_progress

TOOL_FILES = ['tools/project.py', 'tools/disasm.py', 'tools/wip_support.py',
              'tools/probe_compiler.py', 'tools/progress_support.py', 'tools/link_backend.py', 'tools/mwcc_support.py', 'tools/compiler.py',
              'semantic/tools/semantic_progress.py']


def validate_candidate(item, tree=ROOT, scratch=None, validate_behavior=True):
    source = (tree / item['source']).resolve()
    if not source.is_relative_to(scratch if scratch is not None else tree / 'semantic/src'):
        raise GateError('candidate source escapes its approved directory')
    profile = (tree / item['profile_path']).resolve()
    if not profile.is_relative_to(tree / 'semantic/profiles'):
        raise GateError('candidate profile must be saved inside Track B')
    if sha256(source.read_bytes()) != item['source_sha256']:
        raise GateError('stale source: ' + str(source))
    if sha256(profile.read_bytes()) != item['profile_sha256']:
        raise GateError('stale compiler profile: ' + str(profile))
    compiler = read_json(profile)
    if sha256(Path(compiler['executable']).read_bytes()) != compiler['executable_sha256']:
        raise GateError('stale compiler binary')
    for required in ('donor_attribution', 'failed_hypotheses', 'next_hypothesis', 'blocker'):
        if required not in item or item[required] is None:
            raise GateError('missing candidate evidence: ' + required)
    behavior = item.get('behavior_validation')
    if not isinstance(behavior, dict) or not isinstance(behavior.get('status'), str) or not behavior['status']:
        raise GateError('missing explicit behavior status/coverage or blocker')
    if behavior.get('semantic_equivalence_proven', False) is not False:
        raise GateError('unsupported semantic-equivalence claim')
    if validate_behavior and 'report' in behavior:
        report_path = (tree / behavior['report']).resolve()
        if not report_path.is_relative_to(tree / 'semantic/behavior'):
            raise GateError('behavior report escapes the saved bank')
        report = read_json(report_path)
        if (sha256(report_path.read_bytes()) != behavior['report_sha256']
                or report['source_sha256'] != item['source_sha256']
                or report['profile_sha256'] != item['profile_sha256']
                or report['semantic_equivalence_proven'] is not False):
            raise GateError('stale or unsupported behavior evidence claim')
    return source, profile


def run(rom_path, recheck=False, scratches=(), output=None):
    if git('branch', '--show-current', root=ROOT) != 'wip/semantic':
        raise GateError('semantic progress belongs only on Track B')
    baseline = read_json(ROOT / 'semantic/baseline.json')
    for name, digest in baseline['analysis_inputs'].items():
        if sha256(Path(name).read_bytes()) != digest:
            raise GateError('analysis dependency changed: ' + name)
    if baseline['original_sha256'] != ORIGINAL_SHA256:
        raise GateError('wrong semantic baseline identity')
    original(rom_path)
    universe_path = ROOT / 'config' / REVISION / baseline['inventory']
    if sha256(universe_path.read_bytes()) != baseline['functions_sha256']:
        raise GateError('function denominator changed; review a new baseline version')
    tools = {name: sha256((ROOT / name).read_bytes()) for name in TOOL_FILES}
    if tools != baseline['tool_hashes']:
        raise GateError('tool implementation changed; review/pin a new baseline')
    items = [(item, None) for item in read_json(ROOT / 'semantic/candidates.json')['candidates']]
    known = {item['source'] for item, _ in items}
    for p in (ROOT / 'semantic/src').rglob('*'):
        if p.suffix in ('.c', '.cpp') and str(p.relative_to(ROOT)) not in known:
            raise GateError('saved draft lacks hash-bound metadata: ' + str(p))
    for directory in scratches:
        directory = Path(directory).resolve()
        for path in sorted(directory.rglob('*.candidate.json')):
            item = read_json(path)
            source = (path.parent / item['source']).resolve()
            if not source.is_relative_to(directory):
                raise GateError('private candidate escapes explicitly supplied scratch')
            item['source'] = str(source)
            items.append((item, directory))
    if scratches and (output is None or not any(output.resolve().is_relative_to(Path(p).resolve()) for p in scratches)):
        raise GateError('scratch preview requires --output inside an explicit scratch directory')
    report_path = ROOT / 'semantic/manifest.json'
    old = read_json(report_path) if report_path.exists() and not recheck else None
    cache = {}
    if old and old['tool_hashes'] == tools and old['original_sha256'] == ORIGINAL_SHA256:
        cache = {item['cache_key']: item for item in old['candidates']}
    results, seen = [], set()
    for item, scratch in items:
        source, profile = validate_candidate(item, scratch=scratch)
        key = sha256(json.dumps([item['source_sha256'], item['profile_sha256'], item['function_id'],
                                 ORIGINAL_SHA256, baseline['functions_sha256'], tools], sort_keys=True).encode())
        if key in seen:
            raise GateError('duplicate source/profile/target candidate')
        seen.add(key)
        if key in cache:
            evidence = dict(cache[key])
            evidence.update(item)
            print('REUSED hash-bound evidence: ' + item['function_id'])
        else:
            evidence = evaluate(source, profile, item['function_id'], rom_path, ROOT)
            evidence.update(item)
            evidence['cache_key'] = key
            print('COMPILED isolated candidate: ' + item['function_id'] + ' -> ' + evidence['metrics']['tier'])
        results.append(evidence)
    def rank(item):
        m = item['metrics']
        return (['S', 'N', 'X'].index(m['tier']), abs(m['candidate_size'] - m['target_size']),
                m['resolved_byte_differences'], m['instruction_differences']
                if m['instruction_differences'] is not None else 10**9, item['source'])
    groups = {}
    for item in results:
        groups.setdefault(item['function_id'], []).append(item)
    best = [min(groups[key], key=rank) for key in sorted(groups)]
    universe = read_json(universe_path)
    counters = dual_counters(universe)
    b_ids = accepted_functions()
    accepted = [item for item in best if item['metrics']['tier'] == 'S' and item['function_id'] not in b_ids]
    counters['B_union_S_functions'] += len(accepted)
    counters['B_union_S_code_bytes'] += sum(item['function']['code_size'] for item in accepted)
    manifest = {'schema': 1, 'strict_baseline_commit': baseline['strict_baseline_commit'],
                'original_sha256': ORIGINAL_SHA256, 'inventory': baseline['inventory'], 'functions_sha256': baseline['functions_sha256'],
                'tool_hashes': tools, 'counter_scope': 'private preview; not banked' if scratches else 'saved tracked candidate bank',
                'analysis_inputs': baseline['analysis_inputs'],
                'candidates': results, 'best': best, 'counters': counters,
                'semantic_equivalence_proven': False,
                'behavior_evidence': baseline.get('behavior_evidence', 'separate, explicitly scoped reports only')}
    if scratches:
        write_json(output, manifest)
        print('Private preview only; canonical progress unchanged')
        return
    summary = saved_progress(report_path, universe, manifest_data=manifest)
    write_json(report_path, manifest)
    tiers = {tier: sum(item['metrics']['tier'] == tier for item in best) for tier in ('S', 'N', 'X')}
    lines = ['# Saved research progress', '',
             'Strict credit is an authoritative Track-A snapshot; drafts never earn B here. No equivalence proof. Comparator masks nothing.', '',
             '| Counter | Baseline | Current |', '| --- | --- | --- |',
             f"| B functions / total | 0 / unknown | {counters['B_functions']} / unknown |",
             f"| B sized code bytes / total | 0 / unknown | {counters['B_code_bytes']} / unknown |",
             f"| B union S functions / total | 0 / unknown | {counters['B_union_S_functions']} / unknown |",
             f"| B union S code bytes / total | 0 / unknown | {counters['B_union_S_code_bytes']} / unknown |", '',
             f"Delta: {counters['B_union_S_functions']} functions, {counters['B_union_S_code_bytes']} bytes; code percentage points unavailable.",
             f"Tiers: B {counters['B_functions']}, S {tiers['S']}, N {tiers['N']}, X {tiers['X']}. Inventory incomplete; never use ROM size as code size.", '',
             '| Function | Tier | Target / candidate bytes | Resolved differing bytes | Differing instructions |',
             '| --- | --- | --- | --- | --- |']
    lines[2:2] = [f"Behavior tested (separate): {summary['behavior']['tested_functions']} functions, {summary['behavior']['passed_cases']} sampled calls; not an S tier or proof.", '']
    for item in best:
        m = item['metrics']
        lines.append(f"| {item['function_id']} | {m['tier']} | {m['target_size']} / {m['candidate_size']} | {m['resolved_byte_differences']} | {m['instruction_differences'] if m['instruction_differences'] is not None else 'incomparable size'} |")
        fn = item['function']
        guide = ['# ' + item['function_id'], '', 'Research only; no semantic proof or B acceptance.', '',
                 'Source: ' + item['source'], 'SHA256: ' + item['source_sha256'],
                 'Profile: ' + item['profile_path'], 'Profile SHA256: ' + item['profile_sha256'],
                 'Target size: ' + str(fn['size']) + '; mode: ' + fn['mode'],
                 'Metrics: ' + json.dumps(m, sort_keys=True),
                 'Donor: ' + json.dumps(item['donor_attribution'], sort_keys=True),
                 'Blocker: ' + item['blocker'], 'Failed hypotheses: ' + json.dumps(item['failed_hypotheses']),
                 'Next hypothesis: ' + item['next_hypothesis'],
                 'Behavior evidence (separate): ' + json.dumps(item.get('behavior_validation', {'status': 'not tested'})), '']
        p = ROOT / 'semantic/guide' / (item['function_id'].replace(':', '-') + '.md')
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text('\n'.join(guide))
    (ROOT / 'semantic/PROGRESS.md').write_text('\n'.join(lines) + '\n')
    print(json.dumps({'counters': counters, 'tiers': tiers}, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--recheck', action='store_true', help='explicitly recompile unchanged inputs for validation')
    parser.add_argument('--status', action='store_true', help='read-only saved evidence, no compilation')
    parser.add_argument('--scratch', type=Path, action='append', default=[])
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    try:
        if args.status:
            print(json.dumps(saved_progress(ROOT / 'semantic/manifest.json',
                                           load_universe()), indent=2))
        else:
            if args.rom is None:
                raise GateError('--rom must explicitly select the legal immutable input')
            run(args.rom, args.recheck, args.scratch, args.output)
        return 0
    except (GateError, OSError, ValueError, KeyError, ImportError, subprocess.SubprocessError) as exc:
        print('SEMANTIC ERROR (no new evidence accepted): ' + str(exc))
        return 2


if __name__ == '__main__':
    raise SystemExit(main())
