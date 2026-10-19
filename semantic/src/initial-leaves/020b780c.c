/* Unknown output record: writes four zero words and preserves value at +0x0c. */
void pvz_020b780c_clear_unknown_words(void *record, unsigned int value) {
    volatile unsigned int *words = (volatile unsigned int *)record;
    words[0] = 0u;
    words[1] = 0u;
    words[2] = 0u;
    words[3] = value;
    words[4] = 0u;
}
