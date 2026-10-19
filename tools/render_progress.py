"""Explicit saved-evidence README rendering. No build, compiler or agents."""
import sys
sys.dont_write_bytecode = True
import argparse
from project import ROOT, load_universe
from progress_support import saved_progress


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--semantic-report', required=True)
    args = parser.parse_args()
    result = saved_progress(args.semantic_report, load_universe())
    c, b, t = result['counters'], result['behavior'], result['tiers']
    # No numerical bar fill: the whole-game denominator is unknown.
    svg = f'''<svg xmlns="http://www.w3.org/2000/svg" width="760" height="170" viewBox="0 0 760 170" role="img" aria-label="Reconstruction evidence; whole-game coverage unknown">
<rect width="760" height="170" rx="14" fill="#101c19"/>
<g font-family="Arial, sans-serif">
<text x="24" y="31" fill="#d6eee1" font-size="16" font-weight="bold">PROJECT PROGRESS</text>
<text x="24" y="57" fill="#a6bdb1" font-size="13">Whole-game coverage: unknown &#183; function inventory incomplete</text>
<rect x="24" y="72" width="712" height="8" rx="4" fill="#33483e"/>
<text x="24" y="111" fill="#8de5ac" font-size="20" font-weight="bold">{c['B_functions']} verified functions</text>
<text x="270" y="111" fill="#a9d9ff" font-size="20" font-weight="bold">{b['tested_functions']} behavior tested</text>
<text x="530" y="111" fill="#e3d69a" font-size="15" font-weight="bold">{t['S']} exact &#183; {t['N']} near &#183; {t['X']} different</text>
<text x="24" y="140" fill="#a6bdb1" font-size="12">{c['B_code_bytes']} accepted code bytes</text>
<text x="270" y="140" fill="#a6bdb1" font-size="12">{b['passed_cases']} sampled calls; no equivalence proof</text>
<text x="530" y="140" fill="#a6bdb1" font-size="12">Isolated draft comparisons</text>
</g></svg>
'''
    (ROOT / 'docs/progress.svg').write_text(svg)
    rows = ['| Counter | Baseline | Current |', '| --- | --- | --- |']
    for label, key in [('Verified functions / total', 'B_functions'),
                       ('Verified code bytes / total', 'B_code_bytes'),
                       ('Verified + locally identical draft functions / total', 'B_union_S_functions'),
                       ('Verified + locally identical draft code bytes / total', 'B_union_S_code_bytes')]:
        rows.append(f'| {label} | 0 / unknown | {c[key]} / unknown |')
    rows += ['', f"Since the baseline: {c['B_functions']} additional verified functions ({c['B_code_bytes']} code bytes); including locally identical drafts, {c['B_union_S_functions']} functions ({c['B_union_S_code_bytes']} code bytes). Percentage-point changes are unavailable.", '',
             f"Separately, **{b['tested_functions']} functions pass {b['passed_cases']} sampled behavior calls**. Draft comparisons: {t['S']} locally identical, {t['N']} near and {t['X']} larger differences. These results overlap and must not be added together."]
    p = ROOT / 'README.md'
    text = p.read_text()
    start, end = '<!-- progress:start -->', '<!-- progress:end -->'
    before, rest = text.split(start, 1)
    _, after = rest.split(end, 1)
    p.write_text(before + start + '\n\n' + '\n'.join(rows) + '\n\n' + end + after)
    print('Rendered saved evidence; no percentage invented and no build started.')


if __name__ == '__main__':
    main()
