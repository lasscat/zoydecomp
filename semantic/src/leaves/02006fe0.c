/*
 * arm9:02006fe0  (8 bytes)
 *
 *   swp  r0, r0, [r1]
 *   bx   lr
 *
 * Atomic exchange: stores the value in r0 to the word addressed by r1 and
 * returns the previous content. The ARM SWP instruction performs exactly
 * this; the closest natural-C spelling is the lock-free exchange builtin.
 */
int pvz_02006fe0(int value, volatile int *target)
{
    return __sync_swap(target, value);
}
