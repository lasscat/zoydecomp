/* Returns a VRAM character-data address computed from the main display
 * control register (DISPCNT) and the BG0 control register.
 *   bits 24..26 of DISPCNT select the VRAM block (0x8000 steps)
 *   bits 2..5 of BG0CNT       select the character base block (0x4000 steps)
 */
int display_char_base(void)
{
    unsigned short bg0cnt = *(volatile unsigned short *)0x04000008u;
    unsigned int dispcnt = *(volatile unsigned int *)0x04000000u;
    unsigned int block = (dispcnt & 0x07000000u) >> 24;
    unsigned int charbase = (bg0cnt & 0x3cu) >> 2;
    return (int)(0x06000000u + (block << 16) + (charbase << 14));
}
