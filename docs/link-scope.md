# Reviewed call and overlay prototype

This extends section placement, not the ROM equality rule. The original BWBE r0
identity, complete-function credit, compiler/profile bindings and full-ROM gate
are unchanged. Retained code, data, constructors, BSS and padding earn no C credit.

## Explicit ARM calls

Each build entry may declare `calls`, a list of configured function IDs. The target
must be a bounded ARM function in the same module, with its own source, symbol,
profile and target hash. Symbols and IDs are unique. Missing `calls` means no calls;
compiler-profile `symbol_values` remains forbidden. Every declared edge must occur
in the compiled object's call relocations. No implicit retained-code target is added.

Only SHT_REL R_ARM_CALL (28) and R_ARM_PC24 (1) text relocations are supported. Both
must refer to an undefined, global, default-visibility function/notype symbol that
names the configured target entry. The relocation must cover a unique, aligned ARM
unconditional BL inside the code extent, with the standard REL addend -8. The target
must fit the direct ARM BL range. RELA, ABS32, weak/hidden targets, interior addends,
Thumb/BLX, indirect calls, external tail branches and veneers are not supported.
An R_ARM_PC24 relocation on B is not a call and is rejected. Unrelocated BL is rejected.

LLD resolves the original compiler object at its measured VMA. Python never patches
the generated instructions. Relocation-free blocks retain their early byte prefilter;
call blocks are compared after linking, including every displacement bit. All allocated
sections must exactly equal the declared retained/C section plan and bytes, then the
complete module and ROM must equal the immutable original. Extra linker sections or
thunks are errors. The existing R_ARM_PREL31 exception remains confined to discarded
compiler `.ARM.exidx` metadata; it does not authorize a text relocation.

Synthetic tests exercise a small natural-C call cluster and hostile ELF fixtures.
These are linker regression tests, not reconstructed DS functions or behavior credit.
A successful unchanged 249-function build alone would not establish an actual DS
call-cluster reconstruction.

The supplied MWCC profile remains valid for accepted relocation-free leaves, but its
measured nonleaf fixture emits SHT_RELA R_ARM_PC24 and allocated `.exceptix` metadata.
That form is still rejected. The working native call-cluster fixture uses Clang
SHT_REL R_ARM_CALL. Synthetic SHT_REL PC24 BL coverage does not claim MWCC nonleaf
compatibility. Supporting its real RELA/exception format needs a separate review.
Clang callers targeting a compiled MWCC leaf are covered separately; this does not
authorize an MWCC nonleaf object.

## One overlay: arm9/ov000

Only ARM9 and `arm9/ov000` are authorized. ov000 must remain uncompressed, flags zero,
and stored size equal to RAM image size. The frozen overlay-table record identifies
its FAT file; that file must identify exactly one existing ROM-layout chunk with the
same offset, length and SHA256. ov000 currently uses `file-0000`. Its function ROM
offset must equal the overlay ROM offset plus its VMA displacement from the load base.

Each module is linked separately. Overlapping VMAs in distinct overlays do not imply
shared ownership or permit cross-module calls. Only the stored image is replaced;
BSS is not synthesized or credited. Functions may not overlap the retained constructor
table/trailer. The FAT, overlay table, constructors, BSS declarations and all other
chunks remain untouched. Compressed overlays, resizing, other overlays/CPUs, Thumb,
cross-module calls and reconstructed allocated data still require separate review.

## Reproduction and remaining work

Run the synthetic suite, then integrate explicit paths with the normal serialized
workflow and a legally supplied original ROM:

```sh
python3 -B -m unittest discover -s tools/tests -v
python3 -B tools/workflow.py finish --rom /absolute/legal/pvz.nds <explicit-files>
python3 -B tools/workflow.py status
```

The handoff records the actual tested scope and results. RNG seed/next retain their
saved compiler nonmatches. The RNG helper also needs a tail-call decision; declaring
BL edges alone cannot unlock its whole lifecycle. Do not relax the call rules or
repeat its cached profiles to manufacture that result.

Current result: the 249-function ARM9 regression ROM is unchanged. No real DS call
cluster or ov000 C function has passed acceptance. Three bounded ov000 candidates
produced zero exact matches in four compiler runs (one compiler failure); no strict
inventory/source/compiler configuration was expanded. Their useful drafts, corrected
layout observations, failed hypotheses and explicit untested behavior are saved on
Track B. In particular, the lookup's corrected selector offset must not inherit its
incorrect first draft's compiler measurements. A new reviewed inventory version is
still needed before any overlay function can be configured for acceptance.
