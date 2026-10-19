/* Clears five word fields of the global structure at 0x021de480 (offsets 0x3c,
   0x38, 0x34, 0x08 and 0x2c in that order). */
void reset_020c7f3c(void)
{
    volatile int *p = (volatile int *)0x021de480;
    p[0x3c / 4] = 0;
    p[0x38 / 4] = 0;
    p[0x34 / 4] = 0;
    p[0x08 / 4] = 0;
    p[0x2c / 4] = 0;
}
