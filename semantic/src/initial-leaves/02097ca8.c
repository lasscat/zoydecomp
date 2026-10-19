/* Unknown byte-map layout: byte base plus byte offset 0x5ef. */
int pvz_02097ca8_test_unknown_bitmap_bit(const void *base,
                                          unsigned int bit_index) {
    const volatile unsigned char *bytes =
        (const volatile unsigned char *)base;
    unsigned int bit = bit_index & 7u;
    unsigned char byte = bytes[(bit_index >> 3) + 0x5efu];
    return (byte & (1u << bit)) != 0u;
}
