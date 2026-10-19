/* Compute the tile-graphics base address used by the current display
   configuration, or 0 when the configuration is not usable.
   0x04000000 = DISPCNT, 0x0400000E = BG0CNT (memory mapped on the DS).
   Display modes 3..5 may force a blank/palette display when BG0 is
   disabled via bit 7; modes 6..7 have no tile background at all. */
unsigned bg_tile_base(void)
{
    unsigned dispcnt = *(volatile unsigned *)0x04000000u;
    unsigned bg0cnt = *(volatile unsigned short *)0x0400000Eu;

    switch (dispcnt & 7u) {
    case 3:
    case 4:
    case 5:
        if ((bg0cnt & 0x80u) != 0u)
            return 0;
        break;
    case 6:
    case 7:
        return 0;
    default:
        break;
    }

    /* display mode selects the 64K bank, BG0 char base block selects the
       offset inside that bank (each block is 16KB). */
    return (unsigned)(((dispcnt & 0x07000000u) >> 24) << 16) + 0x06000000u
         + (((bg0cnt & 0x3Cu) >> 2) << 14);
}
