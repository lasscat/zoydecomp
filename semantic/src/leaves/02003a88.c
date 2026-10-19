/* arm9:02003a88 (12 bytes)
 *
 * Halfword getter for a fixed object.
 *   ldr  r0, [pc, #4]   ; r0 = 0x020fd340  (literal address, not a load of a pointer)
 *   ldrh r0, [r0, #2]   ; return *(unsigned short *)0x020fd342
 *   bx   lr
 *
 * Unknown offset note: the loaded literal 0x020fd340 is the address of a global
 * object whose 16-bit field at +2 is returned. No bounds or flag checks.
 */
unsigned short pvz_02003a88_get(void)
{
    return *(unsigned short *)(0x020fd340u + 2u);
}
