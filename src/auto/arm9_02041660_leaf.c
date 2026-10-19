/*
 * arm9:02041660  (20 bytes)
 *
 *   mov  r1, #0
 *   str  r1, [r0]
 *   str  r1, [r0, #4]
 *   str  r1, [r0, #8]
 *   bx   lr
 *
 * Clears the three leading 32-bit fields of the record (ascending order).
 */
struct Triple_02041660 {
    unsigned int field_0x00;
    unsigned int field_0x04;
    unsigned int field_0x08;
};

void pvz_02041660_leaf(struct Triple_02041660 *record)
{
    record->field_0x00 = 0;
    record->field_0x04 = 0;
    record->field_0x08 = 0;
}
