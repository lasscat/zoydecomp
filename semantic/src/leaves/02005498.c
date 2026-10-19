/* Save a hardware word at 0x04000208, park the base value there, spin until
 * VCOUNT reaches 0, then restore the saved word. */
void sub_02005498(void)
{
    volatile unsigned int *reg = (volatile unsigned int *)0x04000000;
    unsigned int saved = reg[0x82];

    reg[0x82] = (unsigned int)reg;
    while (*(volatile unsigned short *)0x04000006 != 0)
        ;
    reg[0x82] = saved;
}
