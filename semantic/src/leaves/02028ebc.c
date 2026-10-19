/* Fills the first three words of the given array with all-ones. */
void sub_02028ebc(unsigned int *array)
{
    int i;

    for (i = 0; i < 3; i++)
        array[i] = 0xffffffffu;
}
