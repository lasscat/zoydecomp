/*
 * arm9:020c5a38  (12 bytes)
 *
 *   ldr  r1, [pc, #4]        ; literal 0x021db0e0
 *   str  r0, [r1, #8]
 *   bx   lr
 *
 * Stores the argument into the 32-bit slot at 0x021db0e8.
 */
void pvz_020c5a38(unsigned int value)
{
    *(unsigned int *)((char *)0x021db0e0 + 8) = value;
}
