/* arm9:02097cc4 (40 bytes)
 *
 * Sets one bit of a large bitmap embedded in the object.
 *   r0 = self + 0xef
 *   r3 = r0 + 0x500        ; byte base = self + 0x5ef
 *   r0 = 1 << (index & 7)
 *   r2 = r3[index >> 3]
 *   r0 = r0 & 0xff
 *   r2 = r2 | r0
 *   r3[index >> 3] = r2
 *   bx lr
 *
 * Unknown offset note: the bitmap byte base is self + 0x5ef, encoded by the
 * original as two adds; the mask is narrowed to 8 bits before the OR.
 */
void pvz_02097cc4_leaf(char *self, unsigned int index)
{
    unsigned char *base = (unsigned char *)(self + 0xef + 0x500);
    unsigned char mask = (unsigned char)(1u << (index & 7u));
    base[index >> 3] |= mask;
}
