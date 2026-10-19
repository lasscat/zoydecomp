/* arm9:020b7888
 * Swap the two words pointed to by a and b.
 * volatile keeps the original's load-load-store-store order.
 */
void pvz_020b7888_leaf(volatile unsigned int *a, volatile unsigned int *b)
{
    unsigned int tmp = *a;

    *a = *b;
    *b = tmp;
}
