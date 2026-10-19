/* arm9:020018c8
 * Builds a VRAM address from DISPCNT (0x04000000) and the halfword at
 * 0x0400000a.  The pool constant 0x0400000a is inside the reviewed extent.
 *   base = ((DISPCNT & 0x07000000) >> 24) << 16
 *   off  = ((param & 0x3c) >> 2) << 14
 *   return base + 0x06000000 + off
 */
unsigned int sub_020018c8(void)
{
    unsigned int dispcnt = *(volatile unsigned int *)0x04000000;
    unsigned short param = *(volatile unsigned short *)0x0400000au;

    unsigned int base = ((dispcnt & 0x07000000u) >> 24) << 16;
    unsigned int off = (unsigned int)((int)(param & 0x3cu) >> 2) << 14;

    return base + 0x06000000u + off;
}
