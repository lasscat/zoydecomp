/* Clear two words of each of eight records laid out every 12 bytes.
   The original addresses the pair at byte offsets 8 and 12 of the record
   stride, i.e. the last word of one record and the first word of the
   following one, so the eighth record needs one spare word of storage.
   Offsets are written explicitly because the record layout is not fully
   known. */
struct rec12 {
    unsigned f0;
    unsigned f4;
    unsigned f8;
};

void clear_entries(struct rec12 *tbl)
{
    int i;

    for (i = 0; i < 8; i++) {
        unsigned *p = (unsigned *)((char *)tbl + i * 12);

        p[2] = 0;
        p[3] = 0;
    }
}
