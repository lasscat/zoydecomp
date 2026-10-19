# Compiler evidence and supported tools

The original game compiler and its settings have not been identified. The current
verified C build uses a specific Clang 23.1.1 executable and LLD 23.1.1. Eight small
ARM9 functions match with those tools; that does not establish the original compiler.
Executable hashes, versions and settings are recorded under `config/BWBE-r0/`.

## Evidence from the DS binary

The ARM9 entry at 0x02000800 and reviewed RNG functions use ARM instructions, literal
loads, conditional execution and BX returns. Nearby software floating-point calls do
not uniquely identify a compiler. The build-info record at raw ARM9 offset 0xb88
contains SDK metadata, including 0x05047532; it is not a compiler-version record.
ARM7, overlays, ITCM and vendor components may have different toolchains.

CodeWarrior and other compilers remain hypotheses. Desktop build files do not
identify the DS compiler. Distinctive call frames, switches and shared code paths
need further comparison before choosing another profile.

## Optional MWCC installation

Supply legal local copies under ignored `tools/bin/mwccarm/`, with a compatible
runner at `tools/bin/wibo` when required. No compiler or runner is downloaded or
committed by this project. Discover installed versions without running them:

```sh
python3 -B tools/compiler.py discover
```

Choose a compiler explicitly when several are available. To create an exploratory
profile in a private temporary path:

```sh
python3 -B tools/compiler.py profile   --compiler tools/bin/mwccarm/2.0/base/mwccarm.exe   --runner tools/bin/wibo --output /tmp/pvz-mwcc-native.json
python3 -B tools/probe_compiler.py /absolute/path/to/draft.c arm9:02034f40:arm   --profile /tmp/pvz-mwcc-native.json --rom /absolute/path/to/pvz.nds
```

The driver pins executable identities and checks the compiler version and supported
options. Profile creation cannot overwrite tracked configuration. Native execution
failure stops the probe. QEMU requires an explicit `--qemu` option and is not part of
the normal build. Directory version names are not compiler-version evidence.

Earlier bounded seed probes produced 92 or 100 bytes against the 84-byte DS function.
No MWCC game match is claimed. The optional driver has a synthetic-function smoke
test and tests for changed tools, unsupported flags and implicit-fallback prevention.

Per-file settings need measured evidence and a successful complete-ROM verification.
Do not change global flags, weaken comparisons or repeat probes without a new
hypothesis. See [build instructions](building.md) and [work limits](efficiency.md).
