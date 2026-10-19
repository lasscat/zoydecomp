/* Binary search over a table of 12-byte entries.
   Entry: { unsigned start at 0; unsigned len at 4; unsigned tag at 8; }
   The length field has its low bit used as a flag and is masked off.
   Returns the matching entry address, or 0 when the key is not covered. */
struct span {
    unsigned start;
    unsigned len;
    unsigned tag;
};

struct span *find_span(unsigned char *base, int count, unsigned key)
{
    int low = 0;
    int high = count - 1;

    while (low <= high) {
        int mid = (low + high) >> 1;
        struct span *e = (struct span *)(base + mid * 12);

        if (key < e->start)
            high = mid - 1;
        else if (key > e->start + (e->len & ~1u))
            low = mid + 1;
        else
            return e;
    }

    return 0;
}
