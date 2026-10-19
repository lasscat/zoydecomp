/* AUXSPI transfer used by the card/firmware helper: waits for the SPI bus to
   become idle, enables the 32-bit transfer mode on the control register and
   then writes two big-endian words built from the two command halves. */

void auxspi_write(unsigned int a, unsigned int b)
{
    unsigned int x = (b >> 8) | (a << 24);
    unsigned int y = b << 24;
    unsigned int sx;
    unsigned int sy;

    while (*(volatile unsigned int *)0x040001A4 & 0x80000000)
        ;
    *(volatile unsigned short *)0x040001A0 =
        (*(volatile unsigned short *)0x040001A0 & ~0x2000) | 0xC000;
    sx = ((x & 0xff000000) >> 24) | ((x & 0xff0000) >> 8)
       | ((x & 0xff00) << 8) | (x << 24);
    sy = ((y & 0xff000000) >> 24) | ((y & 0xff0000) >> 8)
       | ((y & 0xff00) << 8) | (y << 24);
    *(volatile unsigned int *)0x040001A8 = sx;
    *(volatile unsigned int *)0x040001AC = sy;
}
