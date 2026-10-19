/* Publishes the argument into the fixed global at 0x02108db0 and returns the
 * word that was there before (a plain exchange helper). */
unsigned int pvz_020b8b00_exchange(unsigned int value)
{
    unsigned int *slot = (unsigned int *)0x02108db0;
    unsigned int previous = *slot;

    *slot = value;
    return previous;
}
