int pvz_0201ade0_leaf(unsigned long long v)
{
    v -= (v >> 1) & 0x5555555555555555ULL;
    v = (v & 0x3333333333333333ULL) + ((v >> 2) & 0x3333333333333333ULL);
    v = (v + (v >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    v += v >> 8;
    v += v >> 16;
    v += v >> 32;
    return (int)(v & 0xff);
}
