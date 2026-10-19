/* arm9:020b1b78 (12 bytes)
 *
 * Stores the argument word into the fixed global at 0x02108970.
 *   ldr r1, [pc, #4]   ; r1 = 0x02108970
 *   str r0, [r1]
 *   bx  lr
 */
void pvz_020b1b78_set(int value)
{
    *(int *)0x02108970u = value;
}
