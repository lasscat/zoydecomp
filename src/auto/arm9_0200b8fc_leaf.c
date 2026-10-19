/*
 * arm9:0200b8fc  (20 bytes)
 *
 * Original instructions:
 *   ldr   r0, [r0, #0x14]   ; load 32-bit field at +0x14
 *   tst   r0, #4            ; test bit 2
 *   movne r0, #1
 *   moveq r0, #0
 *   bx    lr
 *
 * Reads a 32-bit status word at offset 0x14 and returns whether bit 2 is set,
 * normalized to 0/1. Record identity and the meaning of bit 2 are unknown.
 */

struct UnknownRecord014 {
    unsigned char unknown_padding_0x00_0x13[0x14];
    unsigned int field_0x14;
};

int pvz_0200b8fc_leaf(struct UnknownRecord014 *record) { return (record->field_0x14 & 4) != 0; }
