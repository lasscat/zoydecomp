/* Program a hardware block based at 0x040004c0 (word 0/1) and its preceding
 * words at 0x040004a4/0x040004a8 from three packed arguments. */
void sub_020bb568(unsigned int a, unsigned int b, unsigned int c)
{
    volatile unsigned int *reg = (volatile unsigned int *)0x040004c0;

    reg[0] = 0x4210ffffu;
    reg[1] = 0x4210ffffu >> 16;
    reg[-7] = ((c << 4) | 0xc0) | (b << 24) | (a << 16);
    reg[-6] = 0;
}
