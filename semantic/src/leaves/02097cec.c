/* Tests one bit of a byte array indexed by a bit number. */
int test_bit(unsigned char *p, unsigned bit)
{
    return (p[0x614 + (bit >> 3)] & (1u << (bit & 7))) != 0;
}
