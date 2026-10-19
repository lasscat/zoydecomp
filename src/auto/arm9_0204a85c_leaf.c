/* arm9:0204a85c (20 bytes)
 * mov r1, #0
 * str r1, [r0]
 * str r1, [r0, #4]
 * str r1, [r0, #8]
 * bx lr
 *
 * Clears three consecutive 32-bit words at offsets 0, 4 and 8.
 */
void pvz_0204a85c_leaf(unsigned int *this)
{
    this[0] = 0;
    this[1] = 0;
    this[2] = 0;
}
