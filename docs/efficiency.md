# Evidence and efficiency tripwires

1. Prioritize connected game systems useful for understanding, mods and ports.
   Define the behavioral question, observable interface and next evidence first.
   Raw function totals and easy-leaf yield do not set the work priority.
2. Preserve existing useful drafts/results. Cache unchanged source SHA256 + compiler
   identity/profile + target + comparator/dependency hashes. The Track-B runner
   reuses hash-bound evidence. An explicit --recheck is for validation, not another
   hypothesis. Tool errors are never successes or cached zero-diff evidence.
3. Every new matching attempt requires a distinct evidence-backed hypothesis and
   an attempt log. After six focused attempts without improvement, stop matching,
   bank the best draft/tests/provenance/failures and review the method. Resume only
   after a documented new binary, ABI, compiler or behavior insight. Six attempts
   is a review tripwire, not permission to spend six probes without evidence.
4. Persistent register/frame/condition-code differences call for liveness/ABI or
   compiler investigation. Never erase register fields, reorder instructions, patch
   generated code or change global flags to manufacture equivalence.
5. Configure/disassemble once per changed input. Use isolated comparisons as a
   prefilter; full-ROM verification belongs to serialized strict integration.
   Missing boundaries, relocations, symbols, stale hashes or failed tools stop
   affected measurements. Never weaken the final gate for speed.
6. Record attempted/exact/failed/cached counts when reviewing a bounded probe batch.
   Existing provisional alerts remain: exact yield below 30% prompts review; below
   20% stops a broad sweep. These govern matching effort, not the value of readable
   behavior-tested drafts. Preserve N/X results and switch to connected evidence.
7. Do not expand parallel agents without authorization. Workers have disjoint private
   scratch assignments; only the coordinator writes/integrates strict sources.
   Status never starts work, builds, probes or agents.
8. Freeze discovery versions and report unknown denominators honestly. Report strict
   B, behavior-tested scope and S/N/X similarity separately; never invent costs,
   durations, semantic proofs or whole-game coverage percentages.
9. Prefer pinned static reference sources. Respect license/file notices and its
   static-only policy; never build the reference or import unverified desktop types.

See reconstruction.md for the system-oriented loop and next-work.json for the
current queue. Reviewed boundaries, build work and saved drafts remain available as evidence.
