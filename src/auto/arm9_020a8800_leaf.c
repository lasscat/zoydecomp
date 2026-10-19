/* arm9:020a8800 (20 bytes)
 *
 * Stores two words into a record only while its busy byte at +0x390 is clear.
 *   r3 = *(unsigned char *)(self + 0x390)
 *   if (r3 == 0) { *(int *)(self + 8) = r1; *(int *)(self + 0xc) = r2; }
 *   bx lr
 *
 * Unknown offset note: +0x390 is a byte flag, +8/+0xc are the written words.
 */
void pvz_020a8800_leaf(char *self, int first, int second)
{
    if (*(unsigned char *)(self + 0x390) == 0) {
        *(int *)(self + 8) = first;
        *(int *)(self + 0xc) = second;
    }
}
