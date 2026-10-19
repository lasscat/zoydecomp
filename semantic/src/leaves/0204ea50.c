/* arm9:0204ea50
 * Swaps the two 32-bit words pointed to by a and b.
 */
void swap_words(unsigned int *a, unsigned int *b)
{
    unsigned int temporary = *a;

    *a = *b;
    *b = temporary;
}
