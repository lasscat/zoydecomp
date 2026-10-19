/* Writes a halfword register assembled from five bit fields.
 * Register 0x0400100A keeps the two bits of mask 0x43; the remaining fields are
 * inserted at bits 14, 7, 8, 2 and 13 from a, b, c, d and e respectively. */
void sub_020b384c(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100au;
    unsigned int value = *reg;

    value = (value & 0x43u) | (a << 14) | (b << 7) | (c << 8) | (d << 2) | (e << 13);
    *reg = value;
}
