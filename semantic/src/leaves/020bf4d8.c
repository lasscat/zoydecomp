/*
 * arm9:020bf4d8  (20 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r0, [pc, #0xc]        ; r0 = 0x021d4914
 *   mov  r1, #0
 *   str  r1, [r0, #4]          ; block->field_0x04 = 0
 *   str  r1, [r0, #0x24]       ; block->field_0x24 = 0
 *   bx   lr
 *
 * Clears the two 32-bit words at +0x04 and +0x24 of the fixed block at
 * 0x021d4914. Field meanings are unknown.
 */
void pvz_020bf4d8_leaf(void)
{
    volatile unsigned int *block = (volatile unsigned int *)0x021d4914u;

    block[1] = 0;
    block[9] = 0;
}
