/* Writes four packed fields into the 16-bit register at 0x0400100C,
   keeping the bits outside mask 0x43. */
void func_020bd3e0(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100Cu;
    unsigned int old = *reg;
    *reg = (unsigned short)((old & 0x43u) | (a0 << 14) | (a1 << 7) | (a2 << 8) | (a3 << 2));
}
