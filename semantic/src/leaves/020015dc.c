/* Screen/map base address helper.
 * Reads DISPCNT (0x04000000) bits 27-29 and BG0CNT (0x04000008) bits 8-12.
 * Returns 0x06000000 + (display mode bits << 16) + (screen base block << 11).
 * The halfword register at 0x04000008 has an unknown name; only bits 8-12 are used. */
unsigned int sub_020015dc(void)
{
    unsigned int bg = *(volatile unsigned short *)0x04000008u;
    unsigned int display = *(volatile unsigned int *)0x04000000u;
    unsigned int mode = (display & 0x38000000u) >> 27;
    unsigned int base = (bg & 0x1f00u) >> 8;

    return 0x06000000u + (mode << 16) + (base << 11);
}
