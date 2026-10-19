/* Decodes eight packed nibbles as an unsigned decimal number.
 * Every nibble must be a decimal digit, otherwise 0 is returned.
 * Nibble i occupies bits (4*i)..(4*i+3); nibble 0 is the least
 * significant decimal digit. */
int decode_packed_decimal(unsigned int value)
{
    int i;
#pragma clang loop unroll(disable)
    for (i = 0; i < 8; i++) {
        if (((value >> (i * 4)) & 0xfu) >= 10u)
            return 0;
    }

    unsigned int total = 0;
    unsigned int place = 1;
#pragma clang loop unroll(disable)
    for (i = 0; i < 8; i++) {
        total += place * ((value >> (i * 4)) & 0xfu);
        place *= 10;
    }
    return (int)total;
}
