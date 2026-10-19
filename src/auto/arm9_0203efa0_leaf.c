/*
 * arm9:0203efa0  (20 bytes)
 *
 * Original instructions:
 *   ldr   r2, [r0]          ; r2 = current word at +0x00
 *   and   r2, r2, #1        ; keep only bit 0
 *   orr   r1, r1, r2        ; new value = argument | preserved bit 0
 *   str   r1, [r0]          ; store back
 *   bx    lr
 *
 * Replaces bits [31:1] of the word at +0x00 with the supplied value while
 * preserving bit 0. The record identity and meaning of bit 0 are unknown.
 */

struct UnknownWord {
    unsigned int field_0x00;
};

void pvz_0203efa0_leaf(struct UnknownWord *record, unsigned int value)
{
    record->field_0x00 = value | (record->field_0x00 & 1);
}
