/* Reads the halfword at global+4. */
unsigned short read_global_h4(void)
{
    volatile unsigned short *base = (volatile unsigned short *)0x020fd340u;
    return base[2];
}
