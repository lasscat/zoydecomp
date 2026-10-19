/* arm9:02042dd8
 * Initialise a free-list style node: two zero words plus a pointer at +0xc to
 * the word at +4.
 * volatile reproduces the original's separate fixed-order stores (clang would
 * merge the two zeroing stores into one STM).
 */
void init_node(volatile unsigned int *p)
{
    p[0] = 0;
    p[1] = 0;
    *(void *volatile *)(p + 3) = (void *)(p + 1);
}
