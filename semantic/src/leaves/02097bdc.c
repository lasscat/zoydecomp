/* arm9:02097bdc
 * Bit-array test.  The array starts 0x5EC bytes into self; bit `index` of
 * that byte array (byte index>>3, bit index&7) is returned as 0/1.
 */
int test_index_bit(const unsigned char *self, unsigned int index)
{
    return (self[0x5ec + (index >> 3)] & (1u << (index & 7))) != 0;
}
