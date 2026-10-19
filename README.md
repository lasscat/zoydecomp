# Plants vs. Zombies DS

A work-in-progress reconstruction of the Nintendo DS game, focused on readable code
for understanding its systems, making mods and supporting future ports.

The verified branch rebuilds the original ROM byte for byte. The research branch
holds unfinished reconstructions, comparison results and behavior tests. The project
is incomplete: the original compiler and the total amount of game code are still
unknown.

![Project progress](docs/progress.svg)

<!-- progress:start -->

| Metric | Baseline | Current | Scoped share |
| --- | --- | --- | --- |
| Verified functions / bounded inventory | 0 / unknown | 133 / 483 | 27.5% |
| Verified code bytes / bounded inventory | 0 / unknown | 2072 / 10840 | 19.1% |
| Whole-game coverage | unknown | unknown | not available |

The share column is scoped to the 483 reviewed *bounded* ARM9 entries; it is a lower bound, not whole-game coverage, because the inventory is incomplete.
Since the baseline: 133 additional verified functions (2072 code bytes). Whole-game percent is unavailable.


<!-- progress:end -->

The scoped share is the honest lower bound of coverage against the reviewed inventory.
Whole-game percentages stay unavailable until the function inventory is complete, and
passing sample behavior tests does not prove correctness for every input or game state.

## Get started

Use a legally obtained **BWBE revision 0** ROM. Game files, assets and proprietary
compiler tools are not included.

```sh
git clone --branch decomp/strict https://github.com/lasscat/zoydecomp.git decomp/strict
cd decomp/strict
python3 -B tools/workflow.py status
```

For builds, supply the ROM path explicitly:

```sh
python3 -B tools/workflow.py prepare --rom /absolute/path/to/pvz.nds
python3 -B tools/workflow.py verify --rom /absolute/path/to/pvz.nds
```

The current C build uses specific, hash-checked Clang, LLD and formatting tools.
See [build instructions](docs/building.md) for dependencies and input hashes.
Other compiler versions are not accepted automatically.

## Contribute

Start with [CONTRIBUTING.md](CONTRIBUTING.md). Work on connected game systems and
explain uncertain names, layouts and assumptions. Useful work includes binary
analysis, readable reconstructions, behavior tests, tooling and documentation.

- [Current work](docs/next-work.json): RNG state handling and related behavior.
- [Research branch](https://github.com/lasscat/zoydecomp/tree/wip/semantic): saved drafts and tests.
- [How results are measured](docs/results.md): verified builds, behavior tests and code comparisons.
- [Reference source and attribution](docs/donors.md): desktop source used to investigate DS behavior.
- [AI contributor prompt](PROMPT.md): the same contribution and verification rules apply to all agents.

Original development tools, tests and documentation are MIT licensed. Reconstructed
game code and third-party material have separate provenance and notices; see
[LICENSE](LICENSE) and [NOTICE.md](NOTICE.md).
