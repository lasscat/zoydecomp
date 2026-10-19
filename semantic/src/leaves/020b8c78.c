/*
 * Reads a 32-bit word and returns its high part when the nibble at bits 4-7
 * is below 4, otherwise returns 0.
 */
unsigned int low_nibble_check(unsigned int *word)
{
    unsigned int v = *word;

    if (((v & 0xf0) >> 4) < 4)
        return (v & ~0xffu) >> 8;

    return 0;
}
