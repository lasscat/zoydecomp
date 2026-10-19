/*
 * arm9:0207ad84  (20 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r2, [pc, #0xc]        ; r2 = 0x020e680c (table base)
 *   mov  r1, #0x2c
 *   mla  r1, r0, r1, r2        ; r1 = index * 0x2c + base
 *   ldr  r0, [r1, #0x24]       ; r0 = element->field_0x24
 *   bx   lr
 *
 * Returns the 32-bit word at +0x24 of the index-th 0x2c-byte element of the
 * table at 0x020e680c. Table meaning is unknown.
 */
unsigned int pvz_0207ad84_leaf(unsigned int index)
{
    return *(volatile unsigned int *)(0x020e680cu + index * 0x2cu + 0x24u);
}
