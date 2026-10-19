/* arm9:0204f61c (40 bytes)
 * mov r2, #0
 * mov r1, #1
 * str r2, [r0]
 * str r2, [r0, #4]
 * str r2, [r0, #8]
 * str r2, [r0, #0xc]
 * str r2, [r0, #0x10]
 * str r1, [r0, #0x14]   ; this->f14 = 1
 * str r2, [r0, #0x18]
 * bx lr
 *
 * Zeroes the words at +0x00..+0x10, sets the word at +0x14 to 1 and
 * zeroes the word at +0x18.
 */
void init_object(unsigned int *this)
{
    this[0] = 0;
    this[1] = 0;
    this[2] = 0;
    this[3] = 0;
    this[4] = 0;
    this[5] = 1;
    this[6] = 0;
}
