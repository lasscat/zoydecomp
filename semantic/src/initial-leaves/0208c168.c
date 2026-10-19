/* Unknown owner layout: word at byte offset 0x28. */
int pvz_0208c168_test_unknown_word_range(void *owner) {
    volatile unsigned int *word = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x28);
    unsigned int value = *word;
    return (value - 0x49u) <= 1u;
}
