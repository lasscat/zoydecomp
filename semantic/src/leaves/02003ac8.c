/*
 * arm9:02003ac8  (12 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r0, [pc, #4]          ; r0 = 0x020fd340
 *   ldrh r0, [r0, #8]          ; r0 = *(unsigned short *)0x020fd348
 *   bx   lr
 *
 * Returns a 16-bit word from a fixed data record at 0x020fd340 (+0x08).
 * The base address is a plain integer constant; the record's meaning is unknown.
 */
unsigned short pvz_02003ac8_leaf(void)
{
    return *(volatile unsigned short *)0x020fd348u;
}
