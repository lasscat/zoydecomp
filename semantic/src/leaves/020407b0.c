/* arm9:020407b0 (8 bytes)
 *
 * Byte getter.
 *   ldrb r0, [r0, #0x40]  ; return *(unsigned char *)(self + 0x40)
 *   bx   lr
 *
 * Unknown offset note: +0x40 is a byte field.
 */
unsigned char pvz_020407b0_get(char *self)
{
    return *(unsigned char *)(self + 0x40);
}
