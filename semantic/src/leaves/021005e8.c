/* Stores a 32-bit value at consecutive words until the word pointer
 * reaches dst + count bytes (count is a byte count). */
void fill_words(int value, int *dst, int count)
{
    int *end = (int *)((char *)dst + count);
    for (;;) {
        if ((int)dst >= (int)end)
            break;
        *dst = value;
        dst++;
    }
}
