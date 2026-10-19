/* arm9:0202ded0
 * Fills a width x height halfword rectangle.  Every cell gets an incrementing
 * low field plus the palette bits (arg6) placed at bit 12; rows advance by
 * stride halfwords.
 *   dst+0, width(1), height(2), stride(3), base = 5th arg, attr = 6th arg
 */
void sub_0202ded0(unsigned short *dst, int width, int height, int stride,
                  unsigned int base, unsigned int attr)
{
    unsigned int high;

    if (height <= 0)
        return;

    high = (attr & 0xfu) << 12;

    do {
        unsigned short *row = dst;
        int x = 0;

        if (width > 0) {
            do {
                *row++ = (unsigned short)(base | high);
                base++;
                x++;
            } while (x < width);
        }
        dst += stride;
        height--;
    } while (height > 0);
}
