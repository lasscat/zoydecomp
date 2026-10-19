# Contributing

Contributions are welcome in binary analysis, readable reconstruction, behavior
tests, tools and documentation. Start with [build instructions](docs/building.md),
[the work queue](docs/next-work.json) and [the current handoff](agent-context/kit/HANDOFF.md).
AI-assisted contributions follow the same rules; use [PROMPT.md](PROMPT.md).

## Set up

Use your own legally obtained BWBE revision 0 ROM. Do not request, download or commit
game binaries, assets, BIOS files, SDKs or proprietary compiler files. Keep local
tools under ignored tools/bin/ and generated data under extract/ or build/.

The verified branch is decomp/strict. The research branch is wip/semantic, in a
separate worktree; see [branch setup](docs/branches.md). Full ROM commands run only
in the verified worktree. The current build needs the exact documented tool profiles;
another installed compiler is not accepted automatically.

## Choose useful work

Propose a connected system with a concrete behavior question. Prefer source that
helps explain the game or supports mods and future ports over a count of easy
functions. Write readable natural ASCII C/C++. Explain uncertain names, layouts,
ownership, signatures, arithmetic and memory assumptions.

Every reference-source correspondence needs independent DS evidence: constants,
control flow, callers, layouts or other measured behavior. Similar names alone are
insufficient. Read [reference attribution](docs/donors.md), preserve notices and
follow the reference repository's static-review-only policy. Do not build it.

## Test and report

Use [the behavior record](docs/behavior-validation.md) for every research draft.
Where feasible, compare it with original DS instructions: returns, output values,
relevant memory and guards, boundary cases and state transitions. Save exact cases
and source/compiler/target/harness hashes. State the model's assumptions and what
remains untested. If testing is blocked, explain why.

The behavior suite includes negative controls using deliberately wrong compiled C
returns and memory effects. A passing sample supports those cases, not all-state
correctness. Report behavior tests separately from code similarity and strict
acceptance; [result definitions](docs/results.md) explain B/S/N/X.

From the research worktree:

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/path/to/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/path/to/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
```

Reuse unchanged hash-bound probes. A new matching attempt needs a new evidence-backed
hypothesis. Stop for review after six nonimproving attempts. Preserve useful drafts,
tests, provenance, diagnostics and failed/next hypotheses on the research branch.

## Submit a change

1. Inspect Git status and preserve existing work. Use explicit file paths when staging.
2. Provide function IDs, source/profile hashes, binary evidence, attribution,
   reproduction commands, actual results, assumptions and limitations.
3. Coordinate strict source changes with the designated maintainer. Workers use
   private scratch directories. Ask before starting parallel agents.
4. Strict acceptance requires complete functions/sections, formatting first, tests,
   linking and complete-ROM byte equality. Only the coordinator integrates. A local
   exact comparison alone is insufficient. Never merge research wholesale.
5. Keep ROMs, assets, tools, generated output, credentials, private notes and personal
   machine paths out of the patch. Run the publication audit before release.

No assembly, instruction arrays, binary stubs, generated-instruction patches or
embedded target bytes may manufacture a C match. Platform-instruction exceptions
need review and remain outside accepted reconstructed-C credit. Never weaken
comparisons, change expected ROM hashes or adjust global flags to force a match.
Tool failures and unsupported relocations are errors, not successful results.

Use normal commits and pushes for public work. Do not reset, stash, delete branches,
rewrite published history or force-push as routine cleanup. Contributor licensing is
scoped by [LICENSE](LICENSE) and [NOTICE.md](NOTICE.md); preserve third-party notices.
