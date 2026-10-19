/* arm9:0204ea50
 * Swaps the two 32-bit words pointed to by a and b.
 */
void pvz_0204ea50_leaf(unsigned int *a, unsigned int *b)
{
    unsigned int temporary = *a;

    *a = *b;
    *b = temporary;
}
