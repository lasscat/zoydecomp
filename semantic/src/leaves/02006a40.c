/* arm9:02006a40
 * Clear the first three 32-bit words of the object (2, 1, 0).
 * volatile reproduces the original's descending store order (clang would
 * otherwise reorder these independent stores to ascending 0, 4, 8).
 */
void clear_three(volatile unsigned int *p)
{
    p[2] = 0;
    p[1] = 0;
    p[0] = 0;
}
