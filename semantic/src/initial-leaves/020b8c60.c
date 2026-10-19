/* Unknown input layout: low nibble of word at +0, shifted down four bits. */
int pvz_020b8c60_decode_unknown_nibble(const void *input) {
    const volatile unsigned int *word =
        (const volatile unsigned int *)input;
    unsigned int value = (*word & 0xf0u) >> 4;
    return value < 4u ? (int)value : -1;
}
