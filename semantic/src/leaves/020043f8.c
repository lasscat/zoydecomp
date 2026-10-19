/*
 * Sets a single bit in one of two 32-bit enable words.
 * Bit indices 0x00-0x5F live in the word at 0x02FFFFB0 (bit index - 0x40);
 * indices 0x60-0xBF live in the following word (bit index - 0x60).
 */
void set_enable_bit(int bit)
{
    unsigned int *word = (unsigned int *)0x02ffffb0;

    if (bit >= 0x60) {
        word++;
        bit -= 0x60;
    } else {
        bit -= 0x40;
    }

    *word |= 0x80000000u >> bit;
}
