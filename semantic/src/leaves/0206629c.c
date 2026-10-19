/* arm9:0206629c  (8 bytes) -- tier target
 * mov r0, #0x50
 * bx lr
 *
 * Returns the constant 0x50 (80). Constant identity is unknown.
 */
unsigned int pvz_0206629c_leaf(void)
{
    return 0x50u;
}
