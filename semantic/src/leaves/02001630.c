/*
 * Returns the VRAM base address of the main background selected by the
 * LCD control registers.
 *   0x04000000 DISPCNT (32-bit): bits 27-29 = VRAM block  (x 0x10000)
 *   0x0400000A BG0CNT (16-bit): bits  8-12 = char base   (x 0x800)
 * Result = 0x06000000 + (block << 16) + (charbase << 11).
 */
unsigned int bg_screen_base(void)
{
    int bgcnt = *(volatile unsigned short *)0x0400000A;
    unsigned int dispcnt = *(volatile unsigned int *)0x04000000;

    return 0x06000000u + (((dispcnt & 0x38000000u) >> 27) << 16)
                       + (((bgcnt & 0x1f00) >> 8) << 11);
}
