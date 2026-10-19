/* Swaps the two words addressed by the arguments. */
void pvz_0203f7b0_swap(unsigned int *left, unsigned int *right)
{
    unsigned int saved = *left;

    *left = *right;
    *right = saved;
}
