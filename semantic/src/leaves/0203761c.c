/*
 * arm9:0203761c  (16 bytes)
 *
 * Original:
 *   mov  r2, #0
 *   str  r1, [r0, #0x24]       ; record->field_0x24 = value
 *   str  r2, [r0, #0x28]       ; record->field_0x28 = 0
 *   bx   lr
 *
 * Stores a 32-bit value at +0x24 and clears the 32-bit word at +0x28.
 * Field meanings are unknown.
 */
void pvz_0203761c_leaf(void *record, unsigned int value)
{
    *(unsigned int *)((char *)record + 0x24) = value;
    *(unsigned int *)((char *)record + 0x28) = 0;
}
