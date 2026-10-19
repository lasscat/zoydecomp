/*
 * arm9:02097b88  (40 bytes)
 *
 * Original:
 *   add  r0, r0, #0x1d8        ; r0 = record->flags_0x1d8
 *   add  r3, r0, #0x400        ; r3 = record->flags_0x5d8
 *   and  r0, r1, #7            ; r0 = bit & 7
 *   mov  r2, #1
 *   mvn  r0, r2, lsl r0        ; r0 = ~(1 << (bit & 7))
 *   ldrb r2, [r3, r1, lsr #3]  ; r2 = byte[bit >> 3]
 *   and  r0, r0, #0xff         ; mask to a byte
 *   and  r0, r2, r0
 *   strb r0, [r3, r1, lsr #3]  ; byte[bit >> 3] = r2 & mask
 *   bx   lr
 *
 * Clears the bit numbered `bit` in the byte array that starts at +0x5d8 of the
 * record (the original reaches it as +0x1d8 plus +0x400). Array meaning is
 * unknown.
 */
void pvz_02097b88_leaf(const void *record, unsigned int bit)
{
    volatile unsigned char *flags =
        (volatile unsigned char *)((const char *)record + 0x5d8);
    unsigned int mask = ~(1u << (bit & 7u)) & 0xffu;

    flags[bit >> 3] = (unsigned char)(flags[bit >> 3] & mask);
}
