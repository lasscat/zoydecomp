/*
 * arm9:020c1090  (12 bytes)
 *
 *   ldr  r1, [pc, #4]        ; literal 0x020dce5c (table base)
 *   ldr  r0, [r1, r0, lsl #2]
 *   bx   lr
 *
 * Returns entry `index` of the 32-bit table at 0x020dce5c.
 */
unsigned int pvz_020c1090(unsigned int index)
{
    return ((const unsigned int *)0x020dce5c)[index];
}
