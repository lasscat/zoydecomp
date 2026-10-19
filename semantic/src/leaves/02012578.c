/* arm9:02012578
 * Finds the next set bit in a bitmap starting one past the stored "last"
 * index and wrapping around.  Returns the bit index, or -1 when no bit is
 * set before the search comes full circle.
 *   obj+0x0c : bit count
 *   obj+0x10 : pointer to the 32-bit bitmap words
 *   obj+0x14 : index of the previously used bit
 */
int sub_02012578(char *obj)
{
    int count = *(int *)(obj + 0xc);
    unsigned int *bits = *(unsigned int **)(obj + 0x10);
    int index = *(int *)(obj + 0x14) + 1;
    int bit;
    unsigned int *word;
    int first;

    if (index >= count)
        index = 0;

    first = index;
    bit = index & 0x1f;
    word = bits + (index >> 5);

    for (;;) {
        if (*word & (1u << bit))
            return index;
        index++;
        if (index >= count) {
            index = 0;
            bit = 0;
            word = bits;
        } else {
            bit++;
            if (bit >= 0x20) {
                bit = 0;
                word++;
            }
        }
        if (index == first)
            return -1;
    }
}
