/* arm9:02071280 (20 bytes)
 * cmp r0, #0x30
 * ldrls r1, [pc, #8]    ; r1 = 0x020d5830 (signed byte table)
 * movhi r0, #0
 * ldrsbls r0, [r1, r0]  ; return table[index]
 * bx lr
 *
 * Bounds-checked lookup in a 0x31-entry table of signed bytes at
 * 0x020d5830. Out-of-range indices return 0.
 */
int lookup_byte(unsigned int index)
{
    if (index > 0x30u)
        return 0;
    return *(const signed char *)(0x020D5830u + index);
}
