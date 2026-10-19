/* arm9:0203bf5c
 * Tagged record accessor.  The word at +0 is a tag byte:
 *   bit 0     flag          (1 selects the payload word at +4)
 *   bits 1..7 small value   ("kind", returned in bits 6..0)
 * A bitfield struct reproduces the original's exact tag extraction
 * (lsl #31 / lsrs #31 for the flag, ldrb + lsl #24 / lsr #25 for the kind).
 */
struct tagged_record {
    unsigned int flag : 1;    /* bit 0 of the word at +0 */
    unsigned int kind : 7;    /* bits 1..7 of the word at +0 */
    unsigned int unused : 24; /* bits 8..31 */
    unsigned int payload;     /* +4 */
};

unsigned int tagged_value(const struct tagged_record *record)
{
    if (record->flag)
        return record->payload;

    return record->kind;
}
