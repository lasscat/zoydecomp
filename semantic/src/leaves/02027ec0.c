/*
 * arm9:02027ec0  (24 bytes)
 *
 * Original instructions:
 *   ldrh  r2, [r0]          ; r2 = 16-bit count at +0x00
 *   cmp   r2, r1            ; compare count with index
 *   ldrhi r0, [r0, #4]      ; if (index < count) r0 = pointer at +0x04
 *   addhi r0, r0, r1, lsl #4;                     r0 += index * 16
 *   movls r0, #0            ; else return NULL
 *   bx    lr
 *
 * Bounds-checked accessor into a table of 16-byte entries. The base pointer is
 * stored at offset 0x04 and the entry count is an unsigned 16-bit field at
 * offset 0x00. Entry stride and element layout are unknown.
 */

struct UnknownTable {
    unsigned short count;
    unsigned char unknown_padding_0x02_0x03[2];
    unsigned char *entries;
};

void *pvz_02027ec0_get_entry(struct UnknownTable *table, unsigned int index)
{
    if (index < table->count)
        return table->entries + (index << 4);
    return 0;
}
