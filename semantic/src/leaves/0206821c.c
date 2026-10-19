/*
 * arm9:0206821c  (40 bytes of code; the original's literal pool - if any -
 * would follow the code and lie outside the recorded extent)
 *
 * Original:
 *   ldr  r2, [r1, #0x148]      ; r2 = other->field_0x148 (full word)
 *   ldr  r3, [r0, #0xc]        ; r3 = record->field_0x0c (saved)
 *   lsl  r2, r2, #0x10
 *   lsr  r2, r2, #0x10         ; keep the low 16 bits
 *   str  r2, [r0, #0xc]        ; record->field_0x0c = low half of other's field
 *   str  r3, [r1, #0x148]      ; other->field_0x148 = saved value
 *   ldr  r1, [r0, #0x10]
 *   sub  r1, r1, #1
 *   str  r1, [r0, #0x10]       ; record->field_0x10 -= 1
 *   bx   lr
 *
 * Exchanges a value: the low 16 bits of other->field_0x148 move into
 * record->field_0x0c, the previous value of record->field_0x0c is stored back
 * to other->field_0x148, then the counter at record->field_0x10 is decremented.
 *
 * Note on the `volatile` qualifier: the original performs a full 32-bit read of
 * other->field_0x148 followed by an explicit 16-bit truncation. Without it
 * clang narrows the access to a halfword load; with it the word load is kept.
 * The reconstruction is X: clang materialises the 16-bit mask as `mov/orr`
 * while the original zero-extended with `lsl #16; lsr #16`, so 44 bytes are
 * emitted against the 40 recorded. Field meanings are unknown.
 */
void pvz_0206821c_leaf(void *record, void *other)
{
    unsigned int previous = *(unsigned int *)((char *)record + 0x0c);
    unsigned int exchanged = (unsigned short)*(volatile unsigned int *)((char *)other + 0x148);

    *(unsigned int *)((char *)record + 0x0c) = exchanged;
    *(unsigned int *)((char *)other + 0x148) = previous;
    *(unsigned int *)((char *)record + 0x10) =
        *(unsigned int *)((char *)record + 0x10) - 1;
}
