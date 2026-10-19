/*
 * arm9:02031adc  (28 bytes, no literal pool)
 *
 * Original:
 *   ldr  r1, [r0]              ; r1 = *holder
 *   cmp  r1, #0
 *   ldrne r1, [r0]             ; reload *holder (independent load)
 *   ldrne r0, [r1, #0x118]     ; r0 = object->flags_0x118
 *   orrne r0, r0, #4
 *   strne r0, [r1, #0x118]     ; object->flags_0x118 |= 4
 *   bx   lr
 *
 * Sets bit 2 of the 32-bit flag word at +0x118 of the object referenced by
 * *holder, when that pointer is non-null.
 *
 * Note on the `volatile` qualifier: the original reads the holder slot twice
 * (the test load and the use load are both present in the DS bytes), which a
 * non-volatile form cannot reproduce because clang common-subexpresses the two
 * dereferences. Declaring the holder slot volatile keeps both loads; the object
 * itself is accessed normally. Field meaning is unknown.
 */

struct FlaggedObject {
    unsigned char unknown_00_117[0x118];
    unsigned int flags;            /* +0x118 */
};

void pvz_02031adc_leaf(struct FlaggedObject *volatile *holder)
{
    if (*holder != 0) {
        (*holder)->flags |= 4u;
    }
}
