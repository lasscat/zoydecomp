/* Swaps the two words addressed by the arguments. clang allocates the two
   loaded values to the opposite registers (r2/r3) than the original. */
void swap_0204ea3c(unsigned int *a, unsigned int *b)
{
    unsigned int t = *a;
    *a = *b;
    *b = t;
}
