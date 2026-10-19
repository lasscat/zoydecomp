/* Sets bit `bit` in the flag-byte array at p + 0x5ED. */
void pvz_02097c3c_leaf(char *p, unsigned int bit)
{
    unsigned char *flags = (unsigned char *)(p + 0x5ED);
    unsigned char mask = (unsigned char)(1u << (bit & 7));
    flags[bit >> 3] |= mask;
}
