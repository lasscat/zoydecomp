# Research branch

This branch holds readable unfinished code, comparisons and scoped behavior tests.
It descends from the public verified snapshot. Never merge it wholesale into the
verified branch. The semantic/ directory cannot affect strict ROM builds or counts.
Do not run full ROM preparation, builds, configuration or verification here.

Read CONTRIBUTING.md, docs/reconstruction.md, docs/results.md and
[the behavior record](../docs/behavior-validation.md). Work on connected systems;
record uncertain names, layout, ownership and assumptions. Use the exact documented
reference revision and preserve notices. See systems/rng.md for current work.

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/path/to/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/path/to/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
python3 -B semantic/tools/semantic_progress.py --status
```

Saved comparisons reuse unchanged source/profile/target/tool bindings. --recheck
explicitly recompiles for validation. Compiler failures, stale inputs and unsupported
relocations are errors, never matches. Per-function records are under guide/.

Current saved comparisons: one locally exact draft, seven near and seven larger
differences, including the seed. Separately, five drafts pass 1293 sampled behavior
calls. Seed checks include four persistent-state transition sequences. Predicate
checks use controlled field values; their owner and actual game transitions remain
unknown. All-state, hardware and full-game equivalence are unproven. See BEHAVIOR.md.

Candidate metadata requires explicit behavior status, hashes, provenance, failed
hypotheses and the next evidence-backed hypothesis. If testing is blocked, say why.
Stop after six nonimproving matching attempts and review the method. Native Clang is
the supported path; optional local MWCC requires an explicit profile, with no
implicit QEMU fallback. Compiler inputs remain ignored under tools/bin/.

Use --scratch only for explicitly supplied private directories and --output inside
one of them. Scratch previews do not change saved public progress. Bank useful
source/tests/metadata first so a clean checkout can reproduce the result. Never
publish local notes or private machine details.
