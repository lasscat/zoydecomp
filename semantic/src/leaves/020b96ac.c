/* arm9:020b96ac
 * Writes a packed configuration word to the I/O register at 0x040004A4:
 *   a -> bits 3..0, b -> bits 7..4, c -> bits 11..6, f -> kept unshifted,
 *   e -> bits 23..16, d -> bits 31..24
 * (a=r0, b=r1, c=r2, d=r3, e=first stack argument, f=second stack argument).
 * The original builds the word with a chain of ORs of shifted operands and
 * gets the register address from a literal pool.
 */
void set_packed_register(unsigned int a, unsigned int b, unsigned int c,
                         unsigned int d, unsigned int e, unsigned int f)
{
    *(volatile unsigned int *)0x040004A4u =
        a | (b << 4) | (c << 6) | f | (e << 16) | (d << 24);
}
