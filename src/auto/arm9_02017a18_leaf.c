int pvz_02017a18_leaf(unsigned int a, unsigned int b, int c)
{
    int off;

    if (a > 510 || a < 0xe4)
        return 0;
    if (b > 0x10 || b < 8)
        return 0;
    off = c * ((b + 0x20) * 4 + 0x70) + ((a + 0x26) * 4 + 0x4a + 0x100);
    return off < 5600;
}
