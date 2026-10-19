/* True when bit `bit` of the word array at 0x02FFFC00 + 0x388 is set. */
int func_02008b14(unsigned int bit, unsigned int index) {
    unsigned int v = *(volatile unsigned int *)(0x02FFFC00u + index * 4 + 0x388);
    return (v & (1u << bit)) ? 1 : 0;
}
