/*
 * arm9:02038f48  (28 bytes)
 *
 *   mov  r2, #0
 *   mov  r1, #0xff
 *   str  r2, [r0]
 *   str  r2, [r0, #4]
 *   str  r2, [r0, #8]
 *   str  r1, [r0, #0xc]
 *   bx   lr
 *
 * Initialises a record: the first three words become 0 and the word at
 * +0x0c becomes 0xff.
 */
struct InitRecord_02038f48 {
    unsigned int field_0x00;
    unsigned int field_0x04;
    unsigned int field_0x08;
    unsigned int field_0x0c;
};

void pvz_02038f48(struct InitRecord_02038f48 *record)
{
    record->field_0x00 = 0;
    record->field_0x04 = 0;
    record->field_0x08 = 0;
    record->field_0x0c = 0xff;
}
