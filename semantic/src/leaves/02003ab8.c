/* arm9:02003ab8
 * Read the 16-bit field at 0x020fd340 + 0x10 (fixed global record).
 * The original materialises the base from a literal pool; field meaning unknown.
 */
unsigned short get_field_10(void)
{
    return *(unsigned short *)(0x020FD340u + 0x10);
}
