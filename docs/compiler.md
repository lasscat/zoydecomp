# Compiler evidence and supported tools

The original game compiler and its settings have not been identified. The current
verified C build links functions compiled by **two** reviewed tools side by side:
Clang 23.1.1 (with LLD 23.1.1) and an optional local Metrowerks (MWCC) ARM compiler.
Executable hashes, versions and settings are recorded under `config/BWBE-r0/`. Matching
some functions with a compiler does not identify the original compiler.

## Per-function compiler profiles (mixed toolchains)

`config/BWBE-r0/build.json` names a `profile` for **each** function, so Clang-built and
MWCC-built reconstructions coexist in one module. The linker backend compiles every
entry with its own declared profile and then links the whole module with hash-pinned
LLD; complete-ROM equality still has to hold. To adopt a function that only MWCC
reproduces, point its `build.json` entry at the reviewed MWCC profile instead of the
Clang profile. No global flag is changed and no generated instruction is patched.

## Evidence from the DS binary

The ARM9 entry at 0x02000800 and reviewed RNG functions use ARM instructions, literal
loads, conditional execution and BX returns. Nearby software floating-point calls do
not uniquely identify a compiler. The build-info record at raw ARM9 offset 0xb88
contains SDK metadata, including 0x05047532; it is not a compiler-version record.
ARM7, overlays, ITCM and vendor components may have different toolchains.

No compiler-version string survives in the ROM, so style is the evidence. Corpus data:
many ARM9 leaves byte-match MWCC with `-interworking` and do **not** match Clang, while
other (mostly trivial) leaves match Clang; the sets overlap. MWCC's default returns use
`mov pc, lr`, but the DS uses `bx lr`; `-interworking` makes MWCC emit `bx lr` and is
required for exact matches. Clang, GCC 15 and MWCC each fail a different subset, which
is why per-function profiles are the honest approach.

The call-link prototype has a narrower compiler boundary than relocation-free leaves:
a measured MWCC nonleaf fixture emits SHT_RELA R_ARM_PC24 and allocated `.exceptix`
metadata, which are still rejected. Its existing accepted leaves remain supported.
The working synthetic call cluster uses Clang SHT_REL R_ARM_CALL; see
[call/overlay scope](link-scope.md). Do not infer MWCC call support from mixed-toolchain
leaf success or discard its exception data without a separate review.

## Optional MWCC installation

Supply legal local copies under ignored `tools/bin/mwccarm/`, with a compatible
runner at `tools/bin/wibo` when required. No compiler or runner is downloaded or
committed by this project. Discover installed versions without running them:

```sh
python3 -B tools/compiler.py discover
```

Choose a compiler explicitly when several are available. Create an exploratory
profile in a private path, then review a portable copy before committing it:

```sh
python3 -B tools/compiler.py profile \
  --compiler tools/bin/mwccarm/2.0/base/mwccarm.exe --runner tools/bin/wibo \
  --output /tmp/pvz-mwcc-native.json
```

The reviewed, committed profile `config/BWBE-r0/mwcc20-arm946-o2-interwork.json`
records a **repo-relative** executable (`tools/bin/mwccarm/2.0/base/mwccarm.exe`) and
runner (`tools/bin/wibo`) with their SHA256 identities and the pinned flags
`-proc arm946e -O2 -fp soft -little -nothumb -interworking`. The driver resolves
repo-relative executables against the repository root, so the profile holds no
machine-specific path. It is usable only where that exact compiler and runner are
supplied locally; a clean checkout without them still rebuilds the Clang subset.

Measure an isolated draft with any reviewed profile:

```sh
python3 -B tools/probe_compiler.py /absolute/path/to/draft.c arm9:02034f40:arm \
  --profile config/BWBE-r0/mwcc20-arm946-o2-interwork.json --rom /absolute/legal/pvz.nds
python3 -B tools/probe_compiler.py /absolute/path/to/draft.c arm9:02034f40:arm \
  --profile config/BWBE-r0/clang23-arm946-o2.json --rom /absolute/legal/pvz.nds
```

The driver pins executable identities and checks the compiler version and supported
options. Profile creation cannot overwrite tracked configuration. Native execution
failure stops the probe. QEMU requires an explicit `--qemu` option and is not part of
the normal build. Directory version names are not compiler-version evidence.

Per-file settings need measured evidence and a successful complete-ROM verification.
Do not change global flags, weaken comparisons or repeat probes without a new
hypothesis. See [build instructions](building.md) and [work limits](efficiency.md).
