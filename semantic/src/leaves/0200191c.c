/* Derive the address of the BG2 screen/charter base from DISPCNT and BG2CNT.
 * Returns 0 when the display is in an extended mode that uses BG2CNT bit 7. */
unsigned int sub_0200191c(void)
{
    unsigned int mode = *(volatile unsigned int *)0x04000000 & 7;
    unsigned int cnt = *(volatile unsigned short *)0x0400000c;

    if (mode >= 5 && (cnt & 0x80) != 0)
        return 0;

    return 0x06000000
         + ((*(volatile unsigned int *)0x04000000 & 0x7000000) >> 24 << 16)
         + ((cnt & 0x3c) >> 2 << 14);
}
