/* Packs bits 2..5 of the 16-bit register at 0x0A100004 into bits 14..17. */
unsigned int func_020018fc(void) {
    unsigned int v = *(volatile unsigned short *)0x0A100004u;
    return (((v & 0x3Cu) >> 2) << 14) + 0x06200000u;
}
