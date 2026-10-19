# Troubleshooting

**Wrong ROM or changed extracted input:** use the expected BWBE revision 0 ROM and
check the hashes in building.md. Preserve altered input files for inspection. Never
change the expected hashes or overwrite an altered extraction to make a build pass.

**Compiler, linker or profile error:** verify the executable identity and documented
settings. Unsupported relocations, missing symbols, extra sections and size/mode
mismatches are errors, not successful comparisons. The supported strict backend is
limited to complete standalone ARM9 ARM-mode leaf functions.

**Another build owns the lock:** coordinate with its owner. Do not delete the lock
or start an unguarded build. Only the verified worktree runs the full pipeline.

**Stale verification or behavior report:** refresh it through the appropriate checked
command after reviewing input changes. Status does not build or repair anything.
Missing or modified output ROMs cannot count as current verification.

**Incomplete function discovery:** dsd 0.12.1 misclassifies the shared branch
0x02044684 -> 0x020445a0 near a halfword jump table. Do not invent a function to
silence it. The function inventory remains incomplete. Its repacker also changes
four header bytes; the strict build uses a lossless serializer instead.

**Unsupported behavior-model instruction or memory access:** stop the test. Document
the missing support and add focused model tests before extending it. Do not assume
untested code behaves correctly.

**GitHub access failure:** check connectivity and authentication in the terminal
used for publishing. A connection failure alone does not establish a credential
problem. Keep credentials and diagnostic logs out of Git.
