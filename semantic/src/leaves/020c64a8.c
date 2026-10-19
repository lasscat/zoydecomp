/* Stores the argument at global+0x38. */
void set_global_38(unsigned v)
{
    volatile unsigned *base = (volatile unsigned *)0x021db040u;
    base[0x38 / 4] = v;
}
