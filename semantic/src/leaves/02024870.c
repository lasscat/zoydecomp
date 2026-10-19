/* Decode a little-endian variable-length unsigned value. Bit 0/1/2 of the
 * first byte select 1/2/3/4 byte encodings. Returns the advanced pointer. */
unsigned char *sub_02024870(unsigned char *p, unsigned int *out)
{
    unsigned int b0 = p[0];
    unsigned int b1;
    unsigned int b2;
    unsigned int b3;

    if ((b0 & 1) == 0) {
        *out = b0 >> 1;
        return p + 1;
    }

    b1 = p[1];
    if ((b0 & 2) == 0) {
        *out = b1 | ((b0 >> 2) << 8);
        return p + 2;
    }

    b2 = p[2];
    if ((b0 & 4) == 0) {
        *out = b2 | (b1 << 8) | ((b0 >> 3) << 16);
        return p + 3;
    }

    b3 = p[3];
    *out = b3 | (b2 << 8) | (b1 << 16) | ((b0 >> 3) << 24);
    return p + 4;
}
