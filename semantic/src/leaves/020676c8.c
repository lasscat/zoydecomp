/*
 * arm9:020676c8  (16 bytes)
 *
 * Original instructions:
 *   add  r0, r0, #0x5000    ; r0 += 0x5000
 *   mov  r1, #1
 *   str  r1, [r0, #0xb10]   ; [r0 + 0x5b10] = 1
 *   bx   lr
 *
 * Sets the 32-bit field at offset 0x5b10 of the record to 1. The large fixed
 * offset suggests a big object (e.g. a per-level/global state block); its
 * identity and the field meaning are unknown.
 */

struct UnknownLargeRecord {
    unsigned char unknown_padding_0x0000_0x5b0f[0x5b10];
    unsigned int field_0x5b10;
};

void pvz_020676c8_set_field_0x5b10_to_one(struct UnknownLargeRecord *record)
{
    record->field_0x5b10 = 1;
}
