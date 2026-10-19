/*
 * arm9:020526ac  (28 bytes)  -- tier S (exact bytes)
 *
 * Original instructions:
 *   mov  r1, #0
 *   str  r1, [r0]           ; [r0 + 0x00] = 0
 *   str  r1, [r0, #4]       ; [r0 + 0x04] = 0
 *   strb r1, [r0, #8]       ; [r0 + 0x08] = 0
 *   str  r1, [r0, #0xc]     ; [r0 + 0x0c] = 0
 *   str  r1, [r0, #0x10]    ; [r0 + 0x10] = 0
 *   bx   lr
 *
 * Zero-initializes a fixed-layout record: 32-bit fields at 0x00/0x04/0x0c/0x10
 * and a single byte at 0x08. The original emits the stores in ascending address
 * order (0x00, 0x04, 0x08, 0x0c, 0x10).
 *
 * Note on the `volatile` qualifier: clang's ARM scheduler reorders these
 * independent stores (0x0c,0x10,0x08,0x00,0x04) unless they are volatile, which
 * would not match the original bytes. `volatile` here encodes only the required
 * store ordering; the fields are not actually memory-mapped. Caller at
 * 0x020526c8 zeroes a 0xa0-byte array of 0x14-byte elements with this helper,
 * consistent with an element stride of 0x14.
 */

struct UnknownRecord020 {
    volatile unsigned int field_0x00;
    volatile unsigned int field_0x04;
    volatile unsigned char field_0x08;
    unsigned char unknown_padding_0x09_0x0b[3];
    volatile unsigned int field_0x0c;
    volatile unsigned int field_0x10;
};

void pvz_020526ac_leaf(volatile struct UnknownRecord020 *record)
{
    record->field_0x00 = 0;
    record->field_0x04 = 0;
    record->field_0x08 = 0;
    record->field_0x0c = 0;
    record->field_0x10 = 0;
}
