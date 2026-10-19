/* arm9:0200196c
 * Reads the display control word at 0x04001000 and the halfword at +0x0C.
 * When the low three bits of the control word are 5 or more and bit 7 of the
 * halfword is clear, returns the VRAM base 0x06200000 plus a 0x4000 step taken
 * from bits 2..5 of the halfword.  Otherwise returns 0.
 */
int get_vram_base(void)
{
    int control = *(volatile int *)0x04001000;
    unsigned int mode = *(volatile unsigned short *)(0x04001000 + 0xC);

    if ((control & 7) < 5 || (mode & 0x80) == 0)
        return (int)((((mode & 0x3C) >> 2) << 14) + 0x06200000);
    return 0;
}
