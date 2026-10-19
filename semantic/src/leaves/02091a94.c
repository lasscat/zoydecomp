/* arm9:02091a94
 * Initialise a node: two zero words plus a pointer at +8 to the word at +4.
 * volatile reproduces the original's separate fixed-order stores.
 */
void init_node(volatile unsigned int *p)
{
    p[0] = 0;
    p[1] = 0;
    *(void *volatile *)(p + 2) = (void *)(p + 1);
}
