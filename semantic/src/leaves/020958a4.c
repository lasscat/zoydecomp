/* arm9:020958a4 (8 bytes)
 * ldr r0, [pc]          ; r0 = 0x1b58 (pool word immediately after)
 * bx lr
 *
 * Returns the constant 0x1b58. The original materialises it through a
 * literal pool.
 */
unsigned int constant_0x1b58(void)
{
    return 0x1B58u;
}
