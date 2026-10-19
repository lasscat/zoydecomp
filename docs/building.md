# Reproduction and gate boundaries

Python 3.11+ and Git suffice for the opaque baseline. C reconstruction also requires
the pinned Clang/LLD/clang-format profiles, pyelftools 0.33 and Capstone 5. Supply the original ROM legally;
the exact hash is required. No BIOS, SDK or proprietary compiler is needed for
lossless component reconstruction. Everything unknown, including padding and
header CRCs, remains opaque original data. The builder writes a new output from
56 named component/gap chunks and verifies the actual output hashes. The verifier
also compares every produced byte with the supplied immutable original.

```sh
python3 -B tools/workflow.py prepare --rom /absolute/legal/pvz.nds
python3 -B tools/workflow.py build
python3 -B tools/workflow.py verify --rom /absolute/legal/pvz.nds
python3 -B tools/workflow.py finish --rom /absolute/legal/pvz.nds README.md docs/building.md
```

prepare extracts only. build explicitly repacks. verify always builds, then checks
the actual output. finish/integrate requires explicit regular file paths, formats
C with pinned clang-format and other text whitespace/newlines, stops for review if formatting changes a file,
runs gate tests, rebuilds/verifies, then stages just those files. It never commits
or pushes. The narrow reviewed C backend accepts complete ARM functions in ARM9 and
the stored, uncompressed ov000 image. Only explicitly declared same-module BL edges
between configured complete functions may carry text relocations; see
[the call/overlay scope](link-scope.md). Extra executable sections or allocated data
remain unsupported.
Call/overlay support is a narrow prototype: its regression fixtures are synthetic,
and no ov000 function or actual DS call cluster has yet been accepted. The current
accepted set remains the 249 ARM9 functions; see the handoff for the failed/blocked
system candidates and separate behavior evidence.
config/BWBE-r0/build.json binds each individual source/profile hash, symbol and
reviewed inventory identity. Each entry names its own compiler profile, so functions
reconstructed with different reviewed tools (for example the pinned Clang profile and
the optional local MWCC profile) coexist in one module. It compiles immutable snapshots
through the shared actual driver and links whole modules with original opaque retained
ELF sections using hash-pinned LLD at exact VMAs. No generated instruction is patched. The
compiler's non-runtime .ARM.exidx metadata is discarded only under the reviewed
R_ARM_PREL31 metadata rule; all other text relocation forms remain rejected. All allocated output
sections must match the declared contiguous original/C section plan. The actual
complete output ROM must then equal the immutable original.

finish/integrate accepts configured functions only when accepted.json is explicitly
listed; the acceptance receipt is written only after a successful full-ROM gate.
verify refreshes existing accepted credit and never promotes new configured IDs.
The receipt binds source/config/tool/profile materials, immutable ROM identity and
function IDs. New sources/settings need reviewed evidence and manifest hashes; a
formatting change requires reviewing/updating those bindings before rerunning.
Manual Git actions do not establish acceptance. Unsupported scope remains blocked.

Only the Track-A branch/worktree can run the full pipeline. The advisory flock is
held across formatting, tests, build, verification and staging, shared through the
common Git directory. All coordinators must honor it; manual uncooperative writes
are prohibited. Do not unlink the lock. Failed output construction leaves the
previous verified ROM alone; its saved report is historical evidence, not a new pass.
Existing altered extract files are preserved and cause prepare to stop.

build/BWBE-r0/pvz.nds is the output; verification.json binds the result to current
source/config/tool/profile hashes. Status also checks output presence and its actual
SHA256; missing/tampered outputs are stale. It reads files and Git state only. Use `-B` as shown
to avoid Python cache files. No checksum in generated output can change the expected
ROM identity. No original binary components receive reconstructed-C credit.

Isolated comparison requires legal compiler inputs, pyelftools 0.33 and Capstone 5
shared library. The tested host has clang 23.1.1. Its exact executable hash/version,
ARM946E-S flags and missing symbol policy are recorded in docs/profiles/. This is a
modern exploratory compiler, not the identified original compiler. If the executable
hash changes, create and review a new profile; do not edit historical profile evidence.

```sh
python3 -B tools/probe_compiler.py /absolute/draft.c arm9:02034f40:arm \
  --profile docs/profiles/clang23-arm946-o2.json --rom /absolute/legal/pvz.nds
```

Exit 0: local unmasked S evidence. Exit 1: N/X discrepancy. Exit 2: tool/target error.
The single-function probe still rejects all text relocations except resolved R_ARM_ABS32 against explicitly
provided symbols. Calls/Thumb relocations, RELA and missing symbols block comparison;
they are never masked. Call clusters use the strict module linker, not this single-function
probe. Code/pool boundaries are target evidence, not inferred from
arbitrary bytes. Instructions remain in order with register fields intact.

Fresh checkouts use their own legally supplied ROM via --rom. Copy only a legally available compiler
matching the documented hash to the profile's executable path or review a new profile.
No source build of the reference is part of reproduction.

Matching remains bounded and subordinate to the connected-system workflow in
reconstruction.md. Behavior checks run separately on Track B; no ROM build occurs
there. Read semantic/BEHAVIOR.md in that worktree for reproducible commands, actual
coverage, interpreter limitations and assumptions. Behavior reports cannot change
strict acceptance or instruction-similarity tiers.
