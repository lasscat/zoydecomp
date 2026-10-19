/* Sets bits 8..15 of the display control register (0x04000004) from the low
   byte of the argument and mirrors bit 8 of the argument into bit 7. */
void set_display_control(int value)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x04000004u;
    *reg = (unsigned short)((*reg & 0x3f) | ((unsigned char)value << 8) |
                            ((value & 0x100) >> 1));
}
