/* arm9:020b96d8
 * Packs eight register/stack fields into one 32-bit word and stores it to the
 * hardware register at 0x040004a8.  The pool constant 0x040004a8 is inside the
 * reviewed extent.
 *   word = (a<<26) | (h>>3) | (b<<30) | (c<<20) | (d<<23)
 *        | (e<<16) | (f<<18) | (g<<29)
 */
void sub_020b96d8(unsigned int a, unsigned int b, unsigned int c,
                  unsigned int d, unsigned int e, unsigned int f,
                  unsigned int g, unsigned int h)
{
    *(volatile unsigned int *)0x040004a8 =
        (a << 26) | (h >> 3) | (b << 30) | (c << 20) | (d << 23)
        | (e << 16) | (f << 18) | (g << 29);
}
