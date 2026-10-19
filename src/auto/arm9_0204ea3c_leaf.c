/* Swaps the two words addressed by the arguments. clang allocates the two
   loaded values to the opposite registers (r2/r3) than the original. */
void pvz_0204ea3c_leaf(unsigned int *a, unsigned int *b)
{
    unsigned int t = *a;
    *a = *b;
    *b = t;
}
