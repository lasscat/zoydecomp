# Worker guide

Read AGENTS.md, CONTRIBUTING.md, docs/reconstruction.md and the assigned system
record. The coordinator provides a connected behavior question, specific function
IDs and a private scratch directory. The verified worktree is read-only to workers.
Do not run full ROM preparation/build/verification, edit strict source/configuration,
commit, push, launch agents or change global compiler settings.

Write readable natural ASCII C/C++. Explain uncertain fields, names, signatures,
layout, arithmetic, ownership and memory assumptions. No assembly, instruction
arrays, stubs or embedded target bytes. Review reference licenses and independently
check every DS correspondence; do not build the reference repository.

Test against original DS instructions where feasible: returns, outputs, relevant
memory/guards, boundaries and state transitions. Record exact cases, hashes, scope
and untested behavior using docs/behavior-validation.md. If testing is blocked,
state why. Sample agreement is separate from S/N/X and is not all-state proof.

Reuse unchanged comparisons. A new attempt needs an evidence-backed hypothesis.
After six nonimproving attempts stop for review, preserving the best source, tests,
provenance, diagnostics and failed/next hypotheses. Return artifact paths and exact
metrics. Only the coordinator can accept individual reconstructions after formatting
and complete-ROM equality. Never publish local notes or private machine paths.
