/* arm9:0202960c (28 bytes)
 *
 * Conditional record update. When the word at +0 of the object equals 1, two
 * words are written and the 16-bit flag field at +0x12 gets bit 1 set.
 *   if (*(int *)self == 1) {
 *       flags = *(unsigned short *)(self + 0x12);
 *       *(int *)(self + 4) = r1;
 *       *(int *)(self + 8) = r2;
 *       *(unsigned short *)(self + 0x12) = flags | 2;
 *   }
 *
 * Unknown offset note: +0 is a state word, +4/+8 are word fields, +0x12 is the
 * 16-bit flag field.
 */
void pvz_0202960c_update(char *self, int first, int second)
{
    if (*(int *)self == 1) {
        unsigned short flags = *(unsigned short *)(self + 0x12);
        *(int *)(self + 4) = first;
        *(int *)(self + 8) = second;
        *(unsigned short *)(self + 0x12) = (unsigned short)(flags | 2);
    }
}
