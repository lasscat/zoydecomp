/* Unknown owner layout: word at byte offset 0x5c. */
int pvz_0206901c_test_unknown_word_range(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x5c);
    unsigned int value = *word;
    return (value - 25u) <= 3u;
}
