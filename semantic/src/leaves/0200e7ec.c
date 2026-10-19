/* Resets five word fields of the global context at 0x020ff6e0. The field at
   offset 0x14 receives -3 (mvn #2); the original writes 0x14, 0x18, 0x24, 0x20
   and 0x1c in that order, which is reproduced here. */
void reset_0200e7ec(void)
{
    volatile int *ctx = (volatile int *)0x020ff6e0;
    ctx[0x14 / 4] = -3;
    ctx[0x18 / 4] = 0;
    ctx[0x24 / 4] = 0;
    ctx[0x20 / 4] = 0;
    ctx[0x1c / 4] = 0;
}
