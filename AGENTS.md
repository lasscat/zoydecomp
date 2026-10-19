# PvZ DS coordinator rules

Read README.md, docs/building.md, docs/compiler.md, docs/donors.md and
agent-context/kit/{COORDINATOR_SHORT,HANDOFF,WORKER_SHORT}.md before work.
Read docs/reconstruction.md and docs/efficiency.md for the system-oriented workflow.
The complete function universe and original compiler remain unknown.

- The legally supplied target is BWBE revision 0. Immutable original SHA1:
  fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b. Never change it to pass a gate.
- One coordinator owns Track A, decomp/strict. Only that worktree may prepare,
  build, configure, verify, stage integrations or accept reconstructed C.
  Use tools/workflow.py, which holds one nonblocking common-Git-directory lock.
- Status is read-only: python3 -B tools/workflow.py status. Never launch builds,
  agents or probes as an effect of status. Saved verification can become stale.
- A local exact comparison is only a prefilter. Full output-ROM verification
  after formatting is mandatory. Never mask strict differences, patch generated
  instructions, adjust global flags, or credit retained original binary data.
- The reviewed narrow backend links complete standalone ARM9 leaf C blocks with
  opaque retained sections through LLD. Unreviewed modules/modes/relocations and
  extra code/data are rejected. Never bypass these scope limits.
- Natural ASCII C/C++ only. No asm, instruction arrays, machine-code stubs or
  embedded target bytes to manufacture a reconstructed function. Platform
  instruction exceptions require review and remain outside reconstructed credit.
- No original compiler has been established. Per-file settings need measured
  evidence and full verification. Do not import settings, types or addresses from another game.
- wip/semantic is separate, branched from a verified strict commit. Never merge
  it into Track A. semantic/ must never enter strict sources/config/compiler
  dependencies or counters. Isolated candidate compilation uses private temp dirs.
- Respect reference-source policy: static review only; do not build the reference repository.
  Read docs/donors.md before adapting anything. Every mapping needs DS evidence.
- Preserve every existing edit byte-for-byte. Never reset, stash, blindly restore,
  rewrite published history, force-push, or remove worktrees/branches automatically.
  Other projects and their scratch files are read-only references.
- Stage explicit files only. Never commit ROMs, BIOS, SDKs, compiler executables,
  extract/, build/, local references or opaque binary input. No upstream messages.
- Publishing requires maintainer authorization. Record actual results, never claim
  a push without comparing remote refs. Never publish binary inputs or local notes.
- Do not launch workers or parallel agents without asking the user first.
  A worker, when authorized, writes only its disjoint private scratch assignment.
- Report B and B-union-S together with exact shared denominators; use unavailable
  for unknown totals/percentages. Never call an S result a semantic proof.
- Stop on tool errors, unsupported relocations, stale hashes, overlapping credit,
  wrong targets, concurrent ownership or failed verification. Preserve diagnostics.
- Follow docs/efficiency.md. Never repeat an unchanged source/profile/target probe.
  A near miss needs a new written hypothesis before another attempt.

- Prioritize connected useful game systems over easy-function counts. Write readable
  natural C/C++; document uncertain names/layouts, ownership and assumptions.
- Add reproducible differential checks against DS original instructions where
  feasible: outputs, memory effects, boundaries and state transitions. Record exact
  hashes, coverage, model assumptions and untested behavior.
- Report strict B, behavior-tested reconstructions and instruction similarity
  separately. Behavior testing never earns S or proves 100% equivalence.
- Bank useful unresolved drafts/tests/provenance/failed hypotheses on Track B.
  Reuse unchanged probes; six nonimproving attempts require method review and a new
  evidence-backed hypothesis before continuing. Never merge Track B wholesale.
- Unknown denominators remain unknown; progress bars must show that explicitly.

Behavior validation is a required research record: follow docs/behavior-validation.md.
Use the DS-original oracle and compare outputs, full relevant memory/guards, boundary
cases and state transitions where feasible. Run the saved harness and negative-control
tests, refresh hash-bound reports, then inspect separate behavior status and S/N/X.
If execution is blocked, state why; never label untested code logically equivalent.
The current command is `python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/legal/pvz.nds` from Track B, followed by semantic_progress.py and
`python3 -B -m unittest discover -s semantic/tests -v`. No ROM build runs on Track B.
