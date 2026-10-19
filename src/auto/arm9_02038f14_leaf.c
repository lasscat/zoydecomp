/*
 * arm9:02038f14  (24 bytes)  -- tier S (exact bytes)
 *
 * Original instructions:
 *   mov  r1, #0
 *   strh r1, [r0]           ; [r0 + 0x0] = 0
 *   strh r1, [r0, #2]       ; [r0 + 0x2] = 0
 *   strh r1, [r0, #4]       ; [r0 + 0x4] = 0
 *   strh r1, [r0, #6]       ; [r0 + 0x6] = 0
 *   bx   lr
 *
 * Zeroes four consecutive unsigned 16-bit fields at offsets 0x00..0x06. The
 * original emits the four stores in ascending address order.
 *
 * Note on the `volatile` qualifier: clang's ARM scheduler reorders the four
 * independent stores (it emits 0x06,0x04,0x02,0x00), which does not match the
 * original byte sequence. Declaring the fields volatile forces clang to keep
 * the program's store order, reproducing the original exactly. The fields are
 * not actually memory-mapped; `volatile` here only encodes the required
 * ordering of the zero stores (the same value effect as the non-volatile form).
 */

struct UnknownQuad {
    volatile unsigned short field_0x00;
    volatile unsigned short field_0x02;
    volatile unsigned short field_0x04;
    volatile unsigned short field_0x06;
};

void pvz_02038f14_leaf(volatile struct UnknownQuad *quad)
{
    quad->field_0x00 = 0;
    quad->field_0x02 = 0;
    quad->field_0x04 = 0;
    quad->field_0x06 = 0;
}
