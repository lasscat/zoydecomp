int pvz_02100110_leaf(void)
{
    volatile unsigned short *status = (volatile unsigned short *)0x040002b0;
    volatile unsigned int *counter = (volatile unsigned int *)0x040002b4;

    while (*status & 0x8000) {
    }
    return (int)((*counter + 0x200) >> 10);
}
