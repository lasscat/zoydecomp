/* arm9:02003b28 (12 bytes)
 *
 * Halfword getter for the same fixed object as arm9:02003a88.
 *   ldr  r0, [pc, #4]   ; r0 = 0x020fd340
 *   ldrh r0, [r0, #0x14] ; return *(unsigned short *)0x020fd354
 *   bx   lr
 *
 * Unknown offset note: 0x14 is a 16-bit field of the global object at 0x020fd340.
 */
unsigned short pvz_02003b28_get(void)
{
    return *(unsigned short *)(0x020fd340u + 0x14u);
}
