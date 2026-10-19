# Project handoff

Read AGENTS.md, CONTRIBUTING.md and docs/building.md. Inspect actual Git status,
branches, worktrees and saved verification before working. Preserve existing edits.

## Current results

Target: BWBE revision 0, North American release. Immutable original SHA1:
`fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b`.
SHA256: `43dfad7bcaea611a770034919d3fbf77c0ffe41b81483a0eec7774d7c5c418ad`.

| Evidence | Baseline | Current |
| --- | --- | --- |
| Verified functions / total | 0 / unknown | 249 / unknown |
| Verified code bytes / total | 0 / unknown | 6696 / unknown |
| Verified plus locally identical draft functions / total | 0 / unknown | 249 / unknown |
| Verified plus locally identical draft code bytes / total | 0 / unknown | 6696 / unknown |

Changes: +249 verified functions/+6696 bytes. Percentage-point changes are unknown.
The bounded inventory is functions-v5.json (658 reviewed ARM9 entries); it is still not
a full-game denominator. Research tiers: S 126, N 79, X 439 (644 drafts; the research
snapshot still lists the original 8 accepted functions). Technical strict tier: B 249,
built by mixing per-function Clang and reviewed local MWCC profiles. Behavior is
separate: 6 drafts pass 1948 sampled calls.

The seed draft passes 41 calls, including four persistent-state reseed/rejection
sequences. Four adjacent +0x5c predicates pass 313 calls each: 299 unique boundary/
deterministic values and 14 controlled field inputs. Their owner and actual gameplay
transitions remain unknown. The seed remains X; the four predicates remain N.
The model is a restricted ARM interpreter with focused tests, not validated DS
hardware or a complete emulator. No all-state equivalence proof is claimed.

## Scope unlock phase: results and limitations

- Implemented the narrow prototype in tools/link_backend.py; review
  docs/link-scope.md before extending it. Explicit configured same-module ARM BL
  edges use LLD relocation and exact post-link bytes, with no masked fields or
  generated-instruction patching. The synthetic four-function cluster, retained
  gaps, mixed Clang-caller/MWCC-leaf case and hostile ELF cases pass. Actual MWCC
  nonleaf RELA/exception metadata remains rejected.
- ov000 maps through its frozen overlay/FAT/file-0000 chunk, unchanged stored
  size/hash and retained constructor/BSS declarations. Mapping and dispatch tests
  pass. **No ov000 function or actual DS call cluster has passed the ROM gate.**
  Build configuration, inventory v5 and all 249 accepted C sources are unchanged.
- Three ov000 candidates were bounded before probes: initializer 0x021de5e0,
  coordinate helper 0x021e0b7c, and lookup 0x021fd1ac. Four compiler runs produced
  zero exact matches and one compiler failure; helper #2 was not compiled because
  of its unresolved cross-module call. The initial initializer comparison omitted
  its pool and earns no tier. Review corrected the lookup selector from +0x14 to
  the DS-observed +0x10; corrected source is unmeasured. Its behavior attempt stopped
  before case one at unsupported MVN. No overlay behavior or negative-control pass
  is claimed. Track B saves sources and hash-bound records in semantic/systems/ov000.md
  and semantic/evidence/ov000-system-attempts.json. Do not start another leaf sweep.
- The separate portable four-entry RNG lifecycle oracle now passes **1263 top-level
  original/native calls**, including **626 paired masked/raw draws** on two objects,
  refill/reseed/rejection and a controlled null/default path. Each call checks both
  complete state/guard buffers, the controlled global page, original preserved
  registers/SP and stack guards. Both compiled failure controls are detected.
  The bounded BL extension passes six focused synthetic tests, authorizing only
  0x02034fb4 -> 0x02034f94; the base interpreter remains unchanged. This does not
  identify real default-global ownership or prove all-state/hardware equivalence.
  New files are research-only, outside strict dependencies and canonical S counters.
- Replayed the original canonical behavior suite: six drafts / 1948 sampled calls.
  Refreshed comparison evidence reused all 644 cached entries, compiling zero.
  Canonical tiers remain S 126 / N 79 / X 439 (Track B still has its older B=8
  baseline). All 126 saved S IDs overlap current strict B, so authoritative current
  B and B-union-S both remain **249 functions / 6696 code bytes**, over the same
  unknown whole-game totals. The bounded scope remains **658 functions / 23656
  code bytes** (660 inventory entries, two unbounded). Do not add behavior samples,
  canonical S, synthetic fixtures or retained bytes to B.
- Current unit suites: **63 strict tests**, **25 research tests**, all passing.
  Final serialized finish passed all 63 strict tests and complete-ROM equality after
  formatting. Read-only status confirms `verification_inputs_current: true`, with
  input digest `d9402f69bdc47b5235ba1b6b2432abdc3756931be387cdbbc59fc25a1cc8e9d7`.
  Both immutable hashes above match. Progress rendering is in sync, and publication
  audits of both proposed worktrees pass. No commits or pushes performed;
  strict integration stages explicit files only. Research artifacts remain local
  worktree changes, not a published branch update.

Verified/replay commands (legal original supplied explicitly; no ROM build on B):

```sh
# Track A; finish accepts an explicit regular-file list, never directories.
python3 -B -m unittest discover -s tools/tests -v
python3 -B tools/workflow.py finish --rom /absolute/legal/pvz.nds <explicit-files>
python3 -B tools/workflow.py status
python3 -B tools/render_progress.py --check
python3 -B tools/publication_audit.py --worktree

# Track B; the lifecycle run writes its own hash-bound supplemental report.
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/legal/pvz.nds
python3 -B semantic/tools/rng_lifecycle_check.py --rom /absolute/legal/pvz.nds
python3 -B semantic/tools/rng_lifecycle_check.py --status
python3 -B semantic/tools/semantic_progress.py --rom /absolute/legal/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
python3 -B semantic/tools/semantic_progress.py --status
```

Next action: choose an actual DS call cluster compatible with reviewed relocation
forms, or separately review MWCC RELA/exception metadata and external tail-call
scope. RNG seed/next still need new compiler/ABI evidence before another match probe;
the connected system is behavior-tested but **not strict-complete**. For ov000,
first test a narrow MVN model and corrected lookup layout/return-pointer harness,
then require a new compiler scheduling hypothesis, a reviewed inventory version and
an actual exact prefilter/full-ROM gate. The optional 20-function profile matrix was
not run. Original compiler and complete function universe remain unknown.

## Working rules and commands

Only the coordinator writes strict source/configuration and runs full ROM commands
in decomp/strict under the common Git lock. Format first, run checks, build/link and
compare the entire ROM against the immutable original before accepting individual
reconstructions. Retained original binary data earns no C credit. Research work in
wip/semantic uses isolated compilation and behavior checks; never merge it wholesale.

From the verified worktree:

```sh
python3 -B tools/workflow.py status
python3 -B tools/workflow.py prepare --rom /absolute/path/to/pvz.nds
python3 -B tools/workflow.py verify --rom /absolute/path/to/pvz.nds
python3 -B -m unittest discover -s tools/tests -v
python3 -B tools/publication_audit.py
```

From the research worktree:

```sh
python3 -B semantic/tools/behavior_check.py --system all --rom /absolute/path/to/pvz.nds
python3 -B semantic/tools/semantic_progress.py --rom /absolute/path/to/pvz.nds
python3 -B -m unittest discover -s semantic/tests -v
python3 -B semantic/tools/semantic_progress.py --status
```

The behavior checker detects deliberately wrong compiled C returns and memory writes.
Tests also reject stale source/target/harness data, unsupported instructions/accesses,
wrong counts, missing behavior status, compiler failures and concurrent strict writers.
Clean research checkouts reproduce reports from tracked sources/metadata and legal
inputs, without a ROM build or private scratch files. Normal comparisons reuse
unchanged results; explicit rechecks are for validation.

## Source and tool status

The supported strict build links complete ARM functions compiled
by **two** hash-pinned toolchains: native Clang 23.1.1 (with LLD 23.1.1) and an
optional local Metrowerks (MWCC) ARM compiler. Each `build.json` entry names its own
profile, so the two sets coexist in one module; the whole-ROM gate still decides
acceptance. The key MWCC finding is that `-interworking` is required so returns use
`bx lr` as the DS does. The original compiler remains unidentified (no version string
survives; Clang, GCC 15 and MWCC each fail a different subset). QEMU requires explicit
selection. Local compilers and runners remain ignored and are never committed; the
reviewed MWCC profile is repo-relative, so it holds no machine-specific path. The
narrow linker now has an explicitly configured same-module ARM BL prototype and
uncompressed ov000 chunk mapping; see docs/link-scope.md. Other modules/modes,
cross-module calls, external tail calls, extra sections/data and unsupported
relocations still stop integration. The measured MWCC nonleaf form uses RELA PC24
and `.exceptix`, which remain unsupported; Clang callers may target MWCC leaves.
Synthetic fixtures do not constitute a reconstructed DS call cluster.

The desktop reference revision is 325b2229a7225d73870bb69322eefcda3a45bf8d.
See docs/donors.md for license notices, independently checked MT19937 evidence and
DS-specific differences. No desktop class layout or game-wide behavior is assumed.

Function discovery is incomplete. dsd misclassifies the shared branch at
0x02044684 -> 0x020445a0 beside a halfword jump table; its repacker changes header
bytes and is not used for strict rebuilding. Preserve diagnostics outside Git.

## Next work

The RNG seed/next ownership question is answered: all seed and wrapper callers pass
explicit per-object embedded states seeded from the arm9 0x02005d48 system-time getter;
the global default path appears unreachable. The mt_next draft and its 655-call
transitions are banked.

Matching progress comes from per-function compiler choice. MWCC (`-interworking`)
converts many previously X leaves into exact matches that Clang cannot; remaining
misses are mostly register allocation, if-conversion depth, constant materialization
(address immediates vs literal pool), constant-division strength reduction (the
reviewed MWCC calls `_s32_div_f` where the ROM inlines a magic multiply) and pool
placement. The next phase prioritizes scope unlock and connected systems, not more
ARM9 leaf counts: (1) prove explicit call clusters without masking or instruction
patches; (2) gate one complete ov000 function through its existing stored chunk;
(3) complete a connected readable system with original-instruction differential
tests and a full-ROM gate. The optional 20-function MWCC profile matrix has not run.
It must use a fixed sample and new evidence, not repeat cached seed/next misses.

Waves 7-10 deliberately widened the seed set to unconditional branch targets. That was
essentially a negative result: most extents were mid-routine fragments (live-in
callee-saved registers, backward branches before the extent, or bare `add sp`/`pop`
epilogues). Twenty-five blocks were byte-exact, but they are indistinguishable by
inspection from compiler-shared return/case blocks reached by several tail branches
(for example shared return-0 and return-0x7fffffff tails); independent lane reviews
disagreed on whether any is a real function. None was credited or added to the strict
inventory, and functions-v5 remains the 660-entry reviewed set. Evidence is saved on the
research branch at `semantic/evidence/wave7-10-fragments.json`. The bounded ARM9 leaf
pool is effectively exhausted; further verified gains need overlay/Thumb support,
call-aware reconstruction, or a reviewed tail-call/shared-block classifier.

Read per-function guides and system records before large evidence archives. Save
useful unresolved sources, tests and failed hypotheses. Publication must exclude
private setup/history; the public repository begins with a clean reviewed snapshot.
Do not change program code, compiler settings, hashes or gates during documentation
cleanup. Keep local archives and machine-specific notes outside tracked files.
