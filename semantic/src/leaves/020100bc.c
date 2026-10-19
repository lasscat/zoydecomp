/*
 * arm9:020100bc  (24 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r0, [pc, #0x10]       ; r0 = 0x020fffec
 *   ldrh r0, [r0]              ; r0 = *(unsigned short *)0x020fffec
 *   cmp  r0, #0
 *   movne r0, #0
 *   moveq r0, #3
 *   bx   lr
 *
 * Returns 3 when the 16-bit word at 0x020fffec is zero, otherwise 0. This looks
 * like a "state/mode" selector mapping a zero flag to index 3; unknown meaning.
 */
unsigned int pvz_020100bc_leaf(void)
{
    return *(volatile unsigned short *)0x020fffecu ? 0u : 3u;
}
