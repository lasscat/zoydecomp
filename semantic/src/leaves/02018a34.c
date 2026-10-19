/*
 * arm9:02018a34  (28 bytes of code; the original's two literal-pool words
 * follow the code and lie outside the recorded extent)
 *
 * Original:
 *   ldr  r1, [pc, #0x14]       ; r1 = 0x02fffc30
 *   ldr  r0, [pc, #0x14]       ; r0 = 0x0000ffff
 *   ldrh r1, [r1]              ; r1 = *(unsigned short *)0x02fffc30
 *   cmp  r1, r0
 *   movne r0, #1
 *   moveq r0, #0
 *   bx   lr
 *
 * Returns 1 while the 16-bit word at 0x02fffc30 is not 0xffff, else 0. Unknown
 * flag/counter meaning.
 */
unsigned int pvz_02018a34_leaf(void)
{
    return *(volatile unsigned short *)0x02fffc30u != 0xffffu;
}
