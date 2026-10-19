/* Scans a table of four 6-byte entries and returns the first entry whose
 * first two 16-bit fields contain the requested coordinates.
 * Returns base + 0x12 (the last entry slot) when nothing matches.
 * entry layout: 0x00 a, 0x02 b, 0x04 unused.
 */
struct entry {
    unsigned short a;
    unsigned short b;
    unsigned short c;
};

struct entry *find_region(char *base, int x, int y)
{
    int i;
#pragma clang loop unroll(disable)
    for (i = 0; i < 4; i++) {
        struct entry *e = (struct entry *)(base + i * 6);
        if (x <= (int)e->a && y <= (int)e->b)
            return e;
    }
    return (struct entry *)(base + 0x12);
}
