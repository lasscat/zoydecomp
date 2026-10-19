/* True when bit 0 of the 16-bit display register at 0x04000304 is set. */
int func_0200d6d8(void) {
    return (*(volatile unsigned short *)0x04000304u & 1) ? 1 : 0;
}
