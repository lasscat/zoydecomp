/*
 * arm9:02028168  (16 bytes)
 *
 *   ldr  r1, [r0, #0x14]
 *   add  r1, r1, r0
 *   str  r1, [r0, #0x14]
 *   bx   lr
 *
 * Self-relative fix-up: adds the address of the record itself to the
 * stored 32-bit offset at +0x14 (used for relocatable pointers/offsets).
 */
struct RelocRecord_02028168 {
    unsigned char pad_0x00[0x14];
    unsigned int offset_0x14;
};

void pvz_02028168_leaf(struct RelocRecord_02028168 *record)
{
    record->offset_0x14 += (unsigned int)record;
}
