typedef struct Bits {
    int r00;                /* 0x00 */
    unsigned char *buffer;  /* 0x04 */
    int limit;              /* 0x08 */
    int r0c;                /* 0x0c */
    int r10;                /* 0x10 */
    int pos;                /* 0x14 */
} Bits;

/* Returns the next byte of the bit buffer, or 0 when (pos + 7) / 8 reaches
   the buffer limit.  When the cursor sits on a byte boundary only one byte
   is fetched; otherwise the two straddling bytes are spliced together. */

int bit_read(Bits *p)
{
    int pos = p->pos;
    unsigned char lo;
    unsigned char hi;
    int shift;

    if (p->limit <= (pos + 7) / 8)
        return 0;
    shift = pos % 8;
    if (shift == 0) {
        lo = p->buffer[pos / 8];
        p->pos = pos + 8;
        return lo;
    }
    lo = p->buffer[pos / 8] >> shift;
    hi = p->buffer[pos / 8 + 1] << (8 - shift);
    p->pos = pos + 8;
    return lo | hi;
}
