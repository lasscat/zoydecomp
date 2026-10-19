/* arm9:0210013c
 * Programs the fixed I/O block at 0x04000280: a 16-bit 1 at +0, then the
 * words +0x10 = 0, +0x14 = a, +0x18 = b, +0x1c = 0.
 * (The block address comes from a literal pool in the original; the exact
 * register names are not established.)
 */
void setup_io_block(unsigned int a, unsigned int b)
{
    volatile unsigned char *base = (volatile unsigned char *)0x04000280u;

    *(volatile unsigned short *)base = 1;
    *(volatile unsigned int *)(base + 0x10) = 0;
    *(volatile unsigned int *)(base + 0x14) = a;
    *(volatile unsigned int *)(base + 0x18) = b;
    *(volatile unsigned int *)(base + 0x1c) = 0;
}
