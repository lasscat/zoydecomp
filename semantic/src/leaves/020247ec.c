/* arm9:020247ec
 * Reads a variable-length unsigned integer: the low bits of the first byte
 * say how many bytes follow.  Writes the value to *out and returns the
 * address just past the encoded integer.
 */
unsigned char *sub_020247ec(unsigned char *p, unsigned int *out)
{
    signed char b0 = *(signed char *)p;
    unsigned int b1;
    unsigned int b2;

    if ((b0 & 1) == 0) {
        *out = (unsigned int)(b0 >> 1);
        return p + 1;
    }

    b1 = p[1];
    if ((b0 & 2) == 0) {
        *out = b1 | ((unsigned int)(b0 >> 2) << 8);
        return p + 2;
    }

    b2 = p[2];
    if ((b0 & 4) == 0) {
        *out = b2 | (b1 << 8) | ((unsigned int)(b0 >> 3) << 16);
        return p + 3;
    }

    *out = p[3] | (b2 << 8) | (b1 << 16) | ((unsigned int)(b0 >> 3) << 24);
    return p + 4;
}
