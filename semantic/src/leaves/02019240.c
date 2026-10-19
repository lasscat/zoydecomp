/* Population count (number of set bits) of a 32-bit word. */
int bit_count(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = (x + (x >> 4)) & 0x0f0f0f0fu;
    return (int)((x + (x >> 8) + (x >> 16)) & 0xffu);
}
