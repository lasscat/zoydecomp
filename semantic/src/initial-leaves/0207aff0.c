/* Unknown owner layout: word at byte offset 0x24. */
int pvz_0207aff0_test_unknown_word_set(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x24);
    unsigned int value = *word;
    return value == 0x15u || value == 0x2eu;
}
