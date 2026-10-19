/* arm9:020c6498 (12 bytes)
 *
 * Returns the fixed global halfword at 0x021db040.
 *   ldr  r0, [pc, #4]   ; r0 = 0x021db040
 *   ldrh r0, [r0]
 *   bx   lr
 */
unsigned short pvz_020c6498_get(void)
{
    return *(unsigned short *)0x021db040u;
}
