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

The supported strict build links complete standalone ARM9 ARM leaf functions compiled
by **two** hash-pinned toolchains: native Clang 23.1.1 (with LLD 23.1.1) and an
optional local Metrowerks (MWCC) ARM compiler. Each `build.json` entry names its own
profile, so the two sets coexist in one module; the whole-ROM gate still decides
acceptance. The key MWCC finding is that `-interworking` is required so returns use
`bx lr` as the DS does. The original compiler remains unidentified (no version string
survives; Clang, GCC 15 and MWCC each fail a different subset). QEMU requires explicit
selection. Local compilers and runners remain ignored and are never committed; the
reviewed MWCC profile is repo-relative, so it holds no machine-specific path. The
narrow linker supports complete standalone ARM9 ARM leaf functions; other modes, extra
sections/data and unsupported text relocations stop integration.

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
placement. Next: (1) try reviewed MWCC variants/flags for the constant-division and
if-conversion gaps; (2) keep extending reviewed pool/if-conversion extents; (3)
continue connected-system work (the +0x5c predicate owner) and behavior tests. Keep
matching attempts bounded and require new binary/ABI/compiler evidence before another
shape sweep.

Waves 7-10 deliberately widened the seed set to unconditional branch targets. That was
essentially a negative result: most extents were mid-routine fragments (live-in
callee-saved registers, backward branches before the extent, or bare `add sp`/`pop`
epilogues). Twenty-two blocks were byte-exact, but they are indistinguishable by
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
