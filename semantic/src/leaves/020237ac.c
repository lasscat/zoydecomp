/* Clears the sign bit of the second argument slot, keeps the first slot.
   The first argument's address is taken, so it is read back from its home
   slot; the second slot holds the value that is masked. */
int clear_top_bit(int a, int b)
{
    volatile unsigned *p = (volatile unsigned *)&a;
    unsigned high = p[1];
    unsigned low = a;

    p[1] = high & ~0x80000000u;
    return (int)low;
}
