/* Unknown owner layout: word at byte offset 0x5ae4. */
int pvz_02065a48_test_unknown_word_range(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x5000);
    unsigned int value = word[0x2b9];
    return (value - 2u) <= 1u;
}
