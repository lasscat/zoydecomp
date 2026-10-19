# Project handoff

Read AGENTS.md, CONTRIBUTING.md and docs/building.md. Inspect actual Git status,
branches, worktrees and saved verification before working. Preserve existing edits.

## Current results

Target: BWBE revision 0, North American release. Immutable original SHA1:
`fcc5ec4cfd4fabcbb26dee847d9ed6803e9ad93b`.
SHA256: `43dfad7bcaea611a770034919d3fbf77c0ffe41b81483a0eec7774d7c5c418ad`.

| Evidence | Baseline | Current |
| --- | --- | --- |
| Verified functions / total | 0 / unknown | 8 / unknown |
| Verified code bytes / total | 0 / unknown | 84 / unknown |
| Verified plus locally identical draft functions / total | 0 / unknown | 9 / unknown |
| Verified plus locally identical draft code bytes / total | 0 / unknown | 112 / unknown |

Changes: +8 verified functions/+84 bytes; including locally exact drafts, +9/+112.
Percentage-point changes are unknown. The partial v2 inventory contains 68 entries;
it is not a full-game function or code-size denominator. The v1 inventory is unchanged.
Technical tiers: B8/S1/N7/X7. Behavior is separate: 5 drafts pass 1293 sampled calls.

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

The supported strict build uses hash-pinned native Clang/LLD and formatting tools.
The original compiler remains unknown. Optional local MWCC support is available;
QEMU requires explicit selection. Local compilers and runners remain ignored.
The narrow linker supports complete standalone ARM9 ARM leaf functions. Other modes,
extra sections/data and unsupported text relocations stop integration.

The desktop reference revision is 325b2229a7225d73870bb69322eefcda3a45bf8d.
See docs/donors.md for license notices, independently checked MT19937 evidence and
DS-specific differences. No desktop class layout or game-wide behavior is assumed.

Function discovery is incomplete. dsd misclassifies the shared branch at
0x02044684 -> 0x020445a0 beside a halfword jump table; its repacker changes header
bytes and is not used for strict rebuilding. Preserve diagnostics outside Git.

## Next work

Trace RNG seed-to-next/refill ownership and callers, then extend readable source
and original-instruction transition checks. Next, identify writes to the predicates'
shared +0x5c field and its owner. Keep matching attempts bounded; stop for review
after six nonimproving attempts and require new evidence before continuing.

Read per-function guides and system records before large evidence archives. Save
useful unresolved sources, tests and failed hypotheses. Publication must exclude
private setup/history; the public repository begins with a clean reviewed snapshot.
Do not change program code, compiler settings, hashes or gates during documentation
cleanup. Keep local archives and machine-specific notes outside tracked files.
