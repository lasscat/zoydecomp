/* arm9:0203ffc0
 * Initialises a 3-word range record: start and end are cleared, and the
 * third word (list head sentinel) points at the end field itself (self+4).
 * The record is modelled volatile so the three word stores stay separate and
 * in source order; a plain record lets clang merge the first two stores into
 * one stmib, which is shorter than the original.
 */
struct range_record {
    unsigned int start;   /* +0x0 */
    unsigned int end;     /* +0x4 */
    unsigned int link;    /* +0x8 */
};

void init_range_record(volatile struct range_record *record)
{
    record->start = 0;
    record->end = 0;
    record->link = (unsigned int)((char *)record + 4);
}
