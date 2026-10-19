/*
 * arm9:020662f0  (24 bytes)
 *
 *   lsl  r1, r1, #0x10
 *   ldr  r2, [r0, #0xbc]
 *   lsr  r1, r1, #0x10       ; zero-extend the 16-bit index
 *   mov  r0, #0x280
 *   mla  r0, r1, r0, r2      ; base + index * 0x280
 *   bx   lr
 *
 * Returns the address of the 0x280-byte-strided element `index` of the
 * array whose base pointer is stored at +0xbc of the record. The 16-bit
 * parameter is zero-extended first.
 */
struct LookupTable_020662f0 {
    unsigned char pad_0x00[0xbc];
    char *base_0xbc;
};

char *pvz_020662f0(struct LookupTable_020662f0 *table, unsigned short index)
{
    return table->base_0xbc + (unsigned int)index * 0x280;
}
