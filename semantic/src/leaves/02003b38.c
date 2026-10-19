/* Reads the halfword at global+0x16. */
unsigned short read_global_h16(void)
{
    volatile unsigned short *base = (volatile unsigned short *)0x020fd340u;
    return base[11];
}
