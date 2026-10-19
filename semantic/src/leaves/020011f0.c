/* 0x020011f0: enable/disable the VBlank IRQ bit (bit 3) of REG_DISPSTAT
 * at 0x04000004 and return the previous state of that bit.
 * Only the low halfword of the 32-bit register is touched. */
int DisplayStatVBlankIrq(int enable)
{
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    int previous = *dispstat;
    if (enable != 0)
        *dispstat = *dispstat | 8;
    else
        *dispstat = *dispstat & 0xFFF7;
    return previous & 8;
}
