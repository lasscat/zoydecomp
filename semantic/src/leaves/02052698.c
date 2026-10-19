/* Stores two values into the global pair at 0x021079d8 (second word first). */
void set_global_pair(unsigned a, unsigned b)
{
    volatile unsigned *base = (volatile unsigned *)0x021079d8u;
    base[1] = a;
    base[0] = b;
}
