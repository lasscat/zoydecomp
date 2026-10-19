/* Stores four argument words into four consecutive fields.  The last store is
   written first so that clang keeps it as a separate store rather than folding
   all four into one block store (the original keeps it separate). */
void store_four(unsigned *p, unsigned a, unsigned b, unsigned c, unsigned d)
{
    p[3] = d;
    p[0] = a;
    p[1] = b;
    p[2] = c;
}
