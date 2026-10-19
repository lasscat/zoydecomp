/*
 * arm9:020c6820  (20 bytes)
 *
 * Original:
 *   ldr  r2, [r0, #4]          ; r2 = record->field_0x04
 *   cmp  r2, r1
 *   movne r2, #0
 *   stmibne r0, {r1, r2}       ; record->field_0x04 = value; field_0x08 = 0
 *   bx   lr
 *
 * Stores `value` at +0x04 and clears +0x08, but only when the value at +0x04
 * differs from the new one. Field meanings are unknown.
 */
void pvz_020c6820_leaf(void *record, unsigned int value)
{
    if (*(unsigned int *)((char *)record + 4) != value) {
        *(unsigned int *)((char *)record + 4) = value;
        *(unsigned int *)((char *)record + 8) = 0;
    }
}
