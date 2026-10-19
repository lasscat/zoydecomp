/*
 * arm9:0209211c  (28 bytes)  -- tier X (32-byte candidate)
 *
 * Original instructions:
 *   ldr  r2, [pc, #0x14]     ; literal 0x020e82b0
 *   mov  r1, #0
 *   str  r2, [r0]            ; field 0x00 = fixed tag
 *   str  r1, [r0, #8]
 *   str  r1, [r0, #0xc]
 *   str  r1, [r0, #0x10]
 *   bx   lr
 *
 * Stores a fixed 32-bit tag (0x020e82b0) in the first word and zeroes fields
 * 0x08..0x10; field 0x04 is left untouched.
 *
 * volatile keeps the original's store order (the tag store comes first).
 * The residual difference is the same literal-pool placement: the original
 * loads the tag from the pool word after the function, clang appends its own
 * pool word, so the candidate is four bytes longer than the recorded extent.
 */
struct Record_0209211c {
    volatile unsigned int field_0x00;
    unsigned int field_0x04;
    volatile unsigned int field_0x08;
    volatile unsigned int field_0x0c;
    volatile unsigned int field_0x10;
};

void pvz_0209211c(struct Record_0209211c *record)
{
    record->field_0x00 = 0x020e82b0;
    record->field_0x08 = 0;
    record->field_0x0c = 0;
    record->field_0x10 = 0;
}
