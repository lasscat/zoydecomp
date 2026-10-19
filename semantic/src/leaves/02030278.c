/*
 * arm9:02030278  (12 bytes)
 *
 *   ldr  r0, [pc, #4]        ; literal 0x02104240
 *   ldr  r0, [r0]
 *   bx   lr
 *
 * Returns the 32-bit word stored in the fixed global slot at 0x02104240.
 */
unsigned int pvz_02030278(void)
{
    return *(volatile unsigned int *)0x02104240;
}
