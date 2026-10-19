/* Reports whether the 32-bit global at 0x02100c64 is non-zero. */
int pvz_0201854c_is_global_set(void)
{
    return *(volatile unsigned int *)0x02100c64 != 0;
}
