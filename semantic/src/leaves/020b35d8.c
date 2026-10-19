/*
 * arm9:020b35d8  (20 bytes)  -- tier X (24-byte candidate)
 *
 * Original instructions:
 *   ldr  r2, [pc, #0xc]      ; literal 0x020e9a1c
 *   mov  r1, #1
 *   str  r2, [r0]            ; field 0x00 = fixed tag
 *   str  r1, [r0, #0x9c]
 *   bx   lr
 *
 * Tags a record with the fixed descriptor address 0x020e9a1c and sets the word
 * at +0x9c to 1.
 *
 * volatile keeps the original's tag-store-first order. The residual difference
 * is constant materialisation: the original reads 0x020e9a1c from the literal
 * pool that follows the function, clang emits its own pool load inside the
 * function's text, so the candidate is exactly one pool word (four bytes)
 * longer than the recorded extent.
 */
struct Record_020b35d8 {
    volatile unsigned int field_0x00;
    unsigned char pad_0x04[0x98];
    volatile unsigned int field_0x9c;
};

void pvz_020b35d8(struct Record_020b35d8 *record)
{
    record->field_0x00 = 0x020e9a1c;
    record->field_0x9c = 1;
}
