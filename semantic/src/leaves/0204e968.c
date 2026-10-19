/*
 * arm9:0204e968  (28 bytes)  -- tier S (exact bytes)
 *
 * Original instructions:
 *   mov  r2, #0
 *   str  r2, [r0]
 *   str  r2, [r0, #4]
 *   str  r2, [r0, #8]
 *   str  r1, [r0, #0xc]
 *   str  r2, [r0, #0x10]
 *   bx   lr
 *
 * Initialises a record: four 32-bit fields cleared and the caller value stored
 * at +0x0c, in ascending address order.
 *
 * volatile is used only to reproduce the original's store order; without it
 * clang hoists the +0x0c store in front of the zero stores (a 28-byte candidate
 * with four differing instructions). No memory-mapped behaviour is implied.
 */
struct InitRecord_0204e968 {
    volatile unsigned int field_0x00;
    volatile unsigned int field_0x04;
    volatile unsigned int field_0x08;
    volatile unsigned int field_0x0c;
    volatile unsigned int field_0x10;
};

void pvz_0204e968(struct InitRecord_0204e968 *record, unsigned int value)
{
    record->field_0x00 = 0;
    record->field_0x04 = 0;
    record->field_0x08 = 0;
    record->field_0x0c = value;
    record->field_0x10 = 0;
}
