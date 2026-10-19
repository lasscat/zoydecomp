/*
 * arm9:02068244  (40 bytes)
 *
 *   mov  r2, #0
 *   mov  r1, #1
 *   str  r2, [r0] ... [r0, #0x18]
 *   str  r1, [r0, #0x14]
 *   bx   lr
 *
 * Initialises seven words of a record; all are zero except field 0x14
 * which becomes 1. Stores are emitted in ascending address order.
 */
struct InitRecord_02068244 {
    unsigned int field_0x00;
    unsigned int field_0x04;
    unsigned int field_0x08;
    unsigned int field_0x0c;
    unsigned int field_0x10;
    unsigned int field_0x14;
    unsigned int field_0x18;
};

void pvz_02068244(struct InitRecord_02068244 *record)
{
    record->field_0x00 = 0;
    record->field_0x04 = 0;
    record->field_0x08 = 0;
    record->field_0x0c = 0;
    record->field_0x10 = 0;
    record->field_0x14 = 1;
    record->field_0x18 = 0;
}
