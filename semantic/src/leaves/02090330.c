/* arm9:02090330 (12 bytes)
 *
 * Clears the word at +0.
 *   mov r1, #0
 *   str r1, [r0]
 *   bx  lr
 */
void pvz_02090330_clear(int *self)
{
    *self = 0;
}
