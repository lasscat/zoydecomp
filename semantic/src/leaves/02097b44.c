/* Tests bit `bit` in the flag byte array that starts 0x5d8 bytes into the
 * record: the byte index is bit/8 and the bit index is bit%8. */
int pvz_02097b44_test_flag(unsigned char *record, unsigned int bit)
{
    unsigned char flags = record[0x5d8 + (bit >> 3)];

    return (flags & (1u << (bit & 7))) != 0;
}
