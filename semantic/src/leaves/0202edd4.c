/*
 * arm9:0202edd4  (24 bytes)
 *
 *   ldr  r0, [pc, #0x10]     ; literal 0x021037f0 (global record)
 *   mov  r1, #0
 *   str  r1, [r0, #8]
 *   str  r1, [r0]
 *   str  r1, [r0, #4]
 *   bx   lr
 *
 * Clears the three leading 32-bit fields of the global record at
 * 0x021037f0 in the order 0x08, 0x00, 0x04. The fields are declared
 * volatile because clang otherwise re-orders the independent stores; the
 * original keeps this order.
 */
struct Glob_021037f0 {
    volatile unsigned int field_0x00;
    volatile unsigned int field_0x04;
    volatile unsigned int field_0x08;
};

void pvz_0202edd4(void)
{
    struct Glob_021037f0 *glob = (struct Glob_021037f0 *)0x021037f0;

    glob->field_0x08 = 0;
    glob->field_0x00 = 0;
    glob->field_0x04 = 0;
}
