/* Returns the 32-bit word at global+4. */
unsigned read_global_w4(void)
{
    volatile unsigned *base = (volatile unsigned *)0x020fffe0u;
    return base[1];
}
