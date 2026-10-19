# Contributor prompt

Work on this Plants vs. Zombies DS reconstruction. Read AGENTS.md, README.md,
CONTRIBUTING.md, docs/building.md, docs/reconstruction.md, docs/behavior-validation.md,
docs/efficiency.md and agent-context/kit/HANDOFF.md before changing files. Inspect Git
status, branches, worktrees and saved results. Preserve existing edits.

Use decomp/strict for verified code and wip/semantic for research. Only the designated
coordinator writes strict source/configuration or runs full preparation, builds,
verification and integration. Workers use separate scratch directories and need
explicit authorization. Do not launch more agents automatically.

Prioritize connected systems that help explain the game, mods and future ports.
Write readable natural ASCII C/C++. Document uncertain names, layouts, ownership,
signatures, arithmetic and memory assumptions. Use the exact reference-source
revision in docs/donor-lock.json; inspect licenses and policy before source review.
Do not build that reference repository or assume desktop layouts apply to DS.

For each research draft, record behavior status. Where feasible, test against the
original DS instructions: returns, outputs, relevant memory and guards, boundary
inputs and state transitions. Save source, compiler, target and harness hashes,
exact cases, assumptions and untested behavior. If testing is blocked, explain why.
Sample agreement is not a proof of all-state equivalence or instruction similarity.

From the research worktree, run the applicable checks:

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/path/to/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/path/to/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
python3 -B semantic/tools/semantic_progress.py --status
```

Use existing hash-bound comparisons instead of repeating unchanged probes. A new
matching attempt needs a new evidence-backed hypothesis. After six nonimproving
attempts, stop for review and save the best draft, tests and failed/next hypotheses.

Strict acceptance requires a complete function or section, formatting first, tests
and complete-ROM byte equality. A local exact comparison is only a preliminary
check. Never mask differences, patch generated instructions, embed target bytes,
change the expected hash or adjust global compiler flags to manufacture a match.
Immutable original SHA1: fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b (BWBE revision 0).

Keep research separate; never merge it wholesale into the verified branch. Report
verified code, sampled behavior evidence and S/N/X comparisons separately. Use
unknown for missing totals. Save useful unresolved work with its provenance.

Stage explicit files only. Never commit ROMs, assets, extracted/build output,
proprietary tools, credentials, local notes or machine-specific paths. Do not reset,
stash, rewrite published history, delete branches or push without authorization.
Update the handoff with verified commands, results, limitations and the next action.
