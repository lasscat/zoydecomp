/* arm9:020b778c (20 bytes)
 *
 * Returns the word at +4 when the word at +8 is non-zero, otherwise 0.
 *   r1 = *(int *)(self + 8)
 *   cmp r1, #0
 *   moveq r0, #0
 *   ldrne r0, [r0, #4]
 *   bx lr
 *
 * Unknown offset note: +8 is a presence/count word, +4 the returned word.
 */
int pvz_020b778c_get(char *self)
{
    return *(int *)(self + 8) != 0 ? *(int *)(self + 4) : 0;
}
