"""Render the scoped project-progress block and SVG. No build, compiler or agents.

Two denominators are kept separate and clearly labelled:
  * whole-game coverage stays unknown because the function inventory is incomplete;
  * a scoped percentage is shown against the reviewed *bounded* inventory, which is
    the honest upper bound of the denominator (the real game has more functions).

Run `--write` before committing so the percentage always tracks the verified set, or
`--check` to fail when README.md / docs/progress.svg are out of date. No whole-game
percentage is ever invented; the scoped number is always labelled as such.
"""
import sys
sys.dont_write_bytecode = True
import argparse
from project import ROOT, load_universe, accepted_functions


def counters():
    universe = load_universe()
    bounded = [f for f in universe['functions'] if f.get('size') is not None]
    accepted = accepted_functions()
    by_id = {f['id']: f for f in universe['functions']}
    verified_code = sum(by_id[key]['code_size'] for key in accepted)
    return {
        'verified_functions': len(accepted),
        'verified_code_bytes': verified_code,
        'bounded_functions': len(bounded),
        'bounded_code_bytes': sum(f['code_size'] for f in bounded),
        'function_percent': (100.0 * len(accepted) / len(bounded)) if bounded else 0.0,
        'code_percent': (100.0 * verified_code / sum(f['code_size'] for f in bounded))
        if bounded else 0.0,
    }


def behavior_summary(semantic_report):
    if not semantic_report:
        return None
    from progress_support import saved_progress
    result = saved_progress(semantic_report, load_universe())
    return result['behavior'], result['tiers']


def estimate():
    import json
    p = ROOT / 'config' / 'BWBE-r0' / 'universe-estimate.json'
    if not p.exists():
        return None
    return json.loads(p.read_text())


def render_svg(c, b, est):
    frac = min(1.0, c['function_percent'] / 100.0)
    width = round(712 * frac)
    gfrac = 0.0
    if est and est.get('estimated_functions'):
        gfrac = min(1.0, c['verified_functions'] / est['estimated_functions'])
    gwidth = round(712 * gfrac)
    lines = [
        '<text x="24" y="31" fill="#d6eee1" font-size="16" font-weight="bold">PROJECT PROGRESS</text>',
        '<text x="24" y="55" fill="#a6bdb1" font-size="13">Exact scoped share of the reviewed bounded ARM9 inventory</text>',
        '<rect x="24" y="68" width="712" height="14" rx="7" fill="#33483e"/>',
        f'<rect x="24" y="68" width="{width}" height="14" rx="7" fill="#8de5ac"/>',
        f'<text x="24" y="108" fill="#8de5ac" font-size="22" font-weight="bold">{c["verified_functions"]} reconstructed &#183; {c["function_percent"]:.1f}%</text>',
        f'<text x="24" y="130" fill="#a6bdb1" font-size="13">{c["verified_functions"]} / {c["bounded_functions"]} bounded functions &#183; {c["verified_code_bytes"]} / {c["bounded_code_bytes"]} code bytes ({c["code_percent"]:.1f}%)</text>',
    ]
    if est:
        g_func = 100.0 * c['verified_functions'] / est['estimated_functions']
        g_code = 100.0 * c['verified_code_bytes'] / est['estimated_code_bytes']
        lines += [
            '<rect x="24" y="142" width="712" height="12" rx="6" fill="#2a3a44"/>',
            f'<rect x="24" y="142" width="{gwidth}" height="12" rx="6" fill="#a9d9ff"/>',
            f'<text x="24" y="176" fill="#a9d9ff" font-size="13" font-weight="bold">Global estimate (provisional): {c["verified_functions"]} / ~{est["estimated_functions"]} functions ({g_func:.1f}%) &#183; {g_code:.2f}% of code bytes</text>',
            '<text x="24" y="194" fill="#a6bdb1" font-size="12">Estimate from a discovery census; whole-game coverage remains unknown.</text>',
        ]
    offset = 212 if est else 152
    lines.append(f'<text x="24" y="{offset}" fill="#a6bdb1" font-size="12">Whole-game inventory incomplete.</text>')
    if b:
        behavior, tiers = b
        lines.append(f'<text x="24" y="{offset + 18}" fill="#a9d9ff" font-size="12">{behavior["tested_functions"]} behavior tested / {behavior["passed_cases"]} sampled calls; draft tiers {tiers["S"]} exact, {tiers["N"]} near, {tiers["X"]} different.</text>')
    height = offset + (34 if b else 16) + 6
    body = '\n'.join(lines)
    return (f'<svg xmlns="http://www.w3.org/2000/svg" width="760" height="{height}" '
            f'viewBox="0 0 760 {height}" role="img" aria-label="Scoped and provisional global reconstruction progress">\n'
            f'<rect width="760" height="{height}" rx="14" fill="#101c19"/>\n'
            f'<g font-family="Arial, sans-serif">\n{body}\n</g></svg>\n')


def render_block(c, b, est):
    rows = ['| Metric | Baseline | Current | Share |', '| --- | --- | --- | --- |',
            f"| Verified functions / bounded inventory | 0 / unknown | {c['verified_functions']} / {c['bounded_functions']} | {c['function_percent']:.1f}% (exact, scoped) |",
            f"| Verified code bytes / bounded inventory | 0 / unknown | {c['verified_code_bytes']} / {c['bounded_code_bytes']} | {c['code_percent']:.1f}% (exact, scoped) |",
            ]
    if est:
        g_func = 100.0 * c['verified_functions'] / est['estimated_functions']
        g_code = 100.0 * c['verified_code_bytes'] / est['estimated_code_bytes']
        rows += [
            f"| Estimated whole-game functions | 0 | {c['verified_functions']} / ~{est['estimated_functions']} | ~{g_func:.1f}% (provisional) |",
            f"| Estimated whole-game code bytes | 0 | {c['verified_code_bytes']} / ~{est['estimated_code_bytes']} | ~{g_code:.2f}% (provisional) |",
        ]
    rows += [f"| Frozen whole-game coverage | unknown | unknown | not available |", '',
             f"The **scoped share** is exact for the {c['bounded_functions']} reviewed *bounded* ARM9 entries. "
             f"The **global estimate** is a discovery census (method and caveats in config/BWBE-r0/universe-estimate.json); "
             f"it is provisional, not a frozen whole-game denominator, and the inventory is still incomplete.",
             '',
             f"Since the baseline: {c['verified_functions']} additional verified functions "
             f"({c['verified_code_bytes']} code bytes).",
             ''
             ]
    if b:
        behavior, tiers = b
        rows.append(f"Separately, **{behavior['tested_functions']} functions pass {behavior['passed_cases']} sampled "
                    f"behavior calls**. Saved draft comparisons: {tiers['S']} locally identical, {tiers['N']} near and "
                    f"{tiers['X']} larger differences. These results overlap and must not be added together.")
    return '\n'.join(rows)


def apply_to_readme(block, check):
    p = ROOT / 'README.md'
    text = p.read_text()
    start, end = '<!-- progress:start -->', '<!-- progress:end -->'
    before, rest = text.split(start, 1)
    _, after = rest.split(end, 1)
    updated = before + start + '\n\n' + block + '\n\n' + end + after
    if check:
        return text == updated
    p.write_text(updated)
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--semantic-report', help='optional saved Track-B manifest for behavior/tier counts')
    group = parser.add_mutually_exclusive_group()
    group.add_argument('--write', action='store_true', help='update README.md and docs/progress.svg')
    group.add_argument('--check', action='store_true', help='fail if they are out of date')
    args = parser.parse_args()
    c = counters()
    b = behavior_summary(args.semantic_report)
    est = estimate()
    block = render_block(c, b, est)
    svg = render_svg(c, b, est)
    if args.check:
        readme_ok = apply_to_readme(block, check=True)
        svg_ok = (ROOT / 'docs/progress.svg').read_text() == svg
        if not (readme_ok and svg_ok):
            print('PROGRESS OUT OF DATE: run python3 -B tools/render_progress.py --write')
            return 1
        print('Progress in sync; scoped share is not a whole-game percentage.')
        return 0
    apply_to_readme(block, check=False)
    (ROOT / 'docs/progress.svg').write_text(svg)
    extra = ''
    if est:
        g = 100.0 * c['verified_functions'] / est['estimated_functions']
        extra = f" Provisional global estimate: {c['verified_functions']}/~{est['estimated_functions']} functions ({g:.1f}%)."
    print(f"Rendered scoped progress: {c['verified_functions']}/{c['bounded_functions']} "
          f"functions ({c['function_percent']:.1f}%), {c['verified_code_bytes']}/{c['bounded_code_bytes']} "
          f"code bytes ({c['code_percent']:.1f}%).{extra} Whole-game coverage remains unknown.")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
