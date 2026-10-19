/* arm9:02042d48
 * Same initialiser as 0203ffc0 (identical target bytes): start and end are
 * cleared and the third word points at the end field (self+4).  The record is
 * modelled volatile so the three stores stay separate and in source order,
 * as in the original.
 */
struct range_record2 {
    unsigned int start;   /* +0x0 */
    unsigned int end;     /* +0x4 */
    unsigned int link;    /* +0x8 */
};

void init_range_record2(volatile struct range_record2 *record)
{
    record->start = 0;
    record->end = 0;
    record->link = (unsigned int)((char *)record + 4);
}
