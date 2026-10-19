/* Spin until a memory-mapped ARM9 register changes from its current value.

   0x02FFFC3C is the register address (it is not encodable as an immediate,
   so it is held in the literal pool).  The first sample is taken once and
   kept in a local variable that lives in the stack frame (the original
   stores it at [sp]), then the loop keeps re-reading the register and exits
   as soon as the new sample differs from the first one. */
void pvz_0200ca98_leaf(void)
{
    volatile unsigned *reg = (volatile unsigned *)0x02FFFC3Cu;
    volatile unsigned first;
    unsigned now;

    first = *reg;
    do {
        now = *reg;
    } while (first == now);
}
