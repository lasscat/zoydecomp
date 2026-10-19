/* Clears the first three 32-bit words of an array. */
void clear_three(int *a)
{
    unsigned int i = 0;
#pragma clang loop unroll(disable)
    do {
        a[i] = 0;
        i++;
    } while (i != 3);
}
