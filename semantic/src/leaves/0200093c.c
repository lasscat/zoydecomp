/* Fill a range of 32-bit words with a constant value.
   Original register roles: r0 = value, r1 = destination, r2 = byte length.
   The loop stores the value at *dst and post-increments dst by 4 (a
   single-register stm in the original), comparing the raw pointer against
   the end address. */
void fill_words(unsigned value, unsigned *dst, int nbytes)
{
    unsigned *end = (unsigned *)((char *)dst + nbytes);

    while (dst < end)
        *dst++ = value;
}
