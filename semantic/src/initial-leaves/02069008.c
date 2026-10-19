/* Unknown owner layout: word at byte offset 0x5c. */
int pvz_02069008_test_unknown_word_equal(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x5c);
    return *word == 30u;
}
