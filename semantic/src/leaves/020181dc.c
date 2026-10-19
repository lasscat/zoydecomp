/* arm9:020181dc (16 bytes)
 *
 * Two-level halfword getter through a fixed global pointer.
 *   ldr  r0, [pc, #8]   ; r0 = 0x02100bf0
 *   ldr  r0, [r0, #0xc] ; r0 = *(int *)(0x02100bf0 + 0xc)   (object pointer)
 *   ldrh r0, [r0, #0xc] ; return *(unsigned short *)(object + 0xc)
 *   bx   lr
 *
 * Unknown offset note: +0xc of the global is an object pointer, +0xc of that
 * object is a 16-bit field. The intermediate pointer is not NULL-checked.
 */
unsigned short pvz_020181dc_get(void)
{
    char *object = *(char **)(0x02100bf0u + 0xc);
    return *(unsigned short *)(object + 0xc);
}
