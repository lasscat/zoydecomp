/* Clears the 32-bit slots at offsets 0, 8 and 0x20.  The pointer is volatile so
   the original's three independent stores and their order are reproduced. */
void clear_three(volatile int *p)
{
    p[0] = 0;
    p[2] = 0;
    p[8] = 0;
}
