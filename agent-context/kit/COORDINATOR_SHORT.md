# Coordinator guide

Read AGENTS.md, CONTRIBUTING.md and HANDOFF.md. Inspect actual Git status, working
directories and saved evidence before changing files. Preserve existing work.
One coordinator owns all strict source/configuration writes and integrations.
Authorized workers use disjoint scratch directories; do not expand agent usage.

Prioritize connected systems useful for understanding, mods and ports. Keep source
readable and document unknowns. Follow docs/reconstruction.md, the behavior record
in docs/behavior-validation.md and the queue in docs/next-work.json. Save useful
unresolved work and failed hypotheses on the research branch.

Strict acceptance is unchanged: format first, run checks, build and compare the
entire ROM against the immutable original. Use the common Git lock and explicit
integration paths. No masked differences, generated-code patches or global flag
changes. Never merge the research branch wholesale.

Report B and B union S over the same known or unknown totals; report sampled
behavior separately. Keep source/profile/target/harness hashes current. Reuse
unchanged comparisons. After six nonimproving matching attempts, stop for method
review and require new evidence before continuing.

Use only the verified worktree for full ROM commands. Status is read-only. The
research worktree runs isolated comparisons and behavior checks, never a ROM build.
Inspect the saved results and coverage rather than treating similarity as proof.

Publishing requires an audit of both branches/history and maintainer authorization.
Keep binaries, credentials, private archives and machine-specific notes out of Git.
Do not rewrite public history or change repository visibility as a routine cleanup.
