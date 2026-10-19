/*
 * arm9:0207afc4  (28 bytes)
 *
 *   cmp   r0, #0x10
 *   cmpne r0, #0x13
 *   cmpne r0, #0x18
 *   cmpne r0, #0x2b
 *   moveq r0, #1
 *   movne r0, #0
 *   bx    lr
 *
 * Membership test against the four constants 0x10, 0x13, 0x18, 0x2b,
 * returning 0 or 1.
 */
int pvz_0207afc4(unsigned int value)
{
    return value == 0x10 || value == 0x13 || value == 0x18 || value == 0x2b;
}
