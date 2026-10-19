/* Waits for the divider to finish, then returns the 64-bit quotient after
   adding half of the shift amount for rounding. Reading the result register
   pair as one 64-bit value keeps the low word in r0 and the high in r1. */
unsigned div_result_rounded(void)
{
    unsigned long long v;

    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    v = *(volatile unsigned long long *)0x040002a0;
    v += 0x80000;

    return (unsigned)(v >> 20);
}
