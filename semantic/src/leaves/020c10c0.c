/* arm9:020c10c0 (16 bytes)
 * ldr r1, [pc, #8]      ; r1 = 0x020dd978 (table of 4-byte entries)
 * lsl r0, r0, #2        ; index * 4
 * ldrsh r0, [r1, r0]    ; return the signed halfword at that entry
 * bx lr
 *
 * Returns the first signed 16-bit field of entry `index` of an array of
 * 4-byte records at 0x020dd978.
 */
struct Entry {
    short first;           /* +0x00 */
    short second;          /* +0x02 */
};

int get_entry_first(unsigned int index)
{
    const struct Entry *table = (const struct Entry *)0x020DD978u;
    return table[index].first;
}
