/* arm9:020b1450
 * Zeroes the four 32-bit words at +4..+0x10 and reports 0.
 * The original keeps the zero in r0 (also the return value) while the record
 * pointer stays in r1.
 */
int clear_record_words(void *self)
{
    unsigned int *words = (unsigned int *)((char *)self + 4);

    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;

    return 0;
}
