/* arm9:02039944 (8 bytes)
 *
 * Byte setter.
 *   strb r1, [r0, #0x40]  ; *(unsigned char *)(self + 0x40) = value
 *   bx   lr
 *
 * Unknown offset note: +0x40 is a byte field.
 */
void pvz_02039944_set(char *self, char value)
{
    *(unsigned char *)(self + 0x40) = value;
}
