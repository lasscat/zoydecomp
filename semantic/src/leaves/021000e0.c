/*
 * Programs the division unit at 0x04000280:
 *   +0x00 DIVCNT   = 1
 *   +0x10 DIV_NUMER  = 0 (the numerator comes from the argument below)
 *   +0x14 DIV_DENOM  = 0x1000
 *   +0x18 DIV_RESULT = arg
 *   +0x1C DIVREM     = 0
 * Returns 0.
 */
struct div_unit {
    volatile unsigned short cnt;   /* +0x00 */
    unsigned short pad;            /* +0x02 */
    unsigned char gap[0x0c];       /* +0x04..+0x0F */
    volatile unsigned int numer;   /* +0x10 */
    volatile unsigned int denom;   /* +0x14 */
    volatile unsigned int result;  /* +0x18 */
    volatile unsigned int rem;     /* +0x1C */
};

int div_start(unsigned int numerator)
{
    struct div_unit *hw = (struct div_unit *)0x04000280;

    hw->cnt = 1;
    hw->numer = 0;
    hw->denom = 0x1000;
    hw->result = numerator;
    hw->rem = 0;

    return 0;
}
