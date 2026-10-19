/* Program the 32-bit DS register at 0x0400048C.
   The first write packs the two 16-bit parameters (first argument into the
   high half, second into the low half); the second write stores the third
   parameter in the low half. */
void set_pair(unsigned short lo, unsigned short hi, unsigned short next)
{
    volatile unsigned *reg = (volatile unsigned *)0x0400048Cu;

    *reg = (unsigned)hi << 16 | (unsigned)lo;
    *reg = (unsigned)next;
}
