/* arm9:02074604 (28 bytes)
 *
 * When the state word at +0x3c is 0x2f and the word at +0x54 is zero, the state
 * word is reset to zero.
 *   r1 = *(int *)(self + 0x3c)
 *   if (r1 == 0x2f) {
 *       r1 = *(int *)(self + 0x54)
 *       if (r1 == 0) *(int *)(self + 0x3c) = 0
 *   }
 *   bx lr
 *
 * Unknown offset note: +0x3c state word, +0x54 companion word.
 */
void pvz_02074604_leaf(char *self)
{
    if (*(int *)(self + 0x3c) == 0x2f && *(int *)(self + 0x54) == 0)
        *(int *)(self + 0x3c) = 0;
}
