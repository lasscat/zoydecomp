/*
 * arm9:020b82d0  (16 bytes, no literal pool)
 *
 * Original:
 *   ldr  r2, [r0, #0xc]        ; r2 = record->field_0x0c (returned value)
 *   str  r1, [r0, #8]          ; record->field_0x08 = value
 *   mov  r0, r2                ; return the word loaded before the store
 *   bx   lr
 *
 * Stores `value` at +0x08 and returns the word that was at +0x0c before the
 * store.
 *
 * Note on the `volatile` qualifier: clang moves the +0x08 store in front of the
 * +0x0c read (they do not alias) and emits only three instructions; the DS
 * original reads +0x0c first. `volatile` pins that read-before-write order.
 * Field meanings are unknown.
 */
unsigned int pvz_020b82d0_leaf(volatile unsigned int *record, unsigned int value)
{
    unsigned int previous = record[3];

    record[2] = value;
    return previous;
}
