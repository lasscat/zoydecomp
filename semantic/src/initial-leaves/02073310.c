/* Unknown owner layout: word at byte offset 0x24. */
int pvz_02073310_test_unknown_word_set(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x24);
    unsigned int value = *word;
    return value == 1u || value == 41u || value == 9u;
}
