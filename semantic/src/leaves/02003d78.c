/* arm9:02003d78
 * Clear the 32-bit word pair at the fixed global 0x027e0060 ([1] then [0]).
 */
void clear_global_pair(void)
{
    volatile unsigned int *p = (volatile unsigned int *)0x027E0060u;

    p[1] = 0;
    p[0] = 0;
}
