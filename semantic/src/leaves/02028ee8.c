/*
 * arm9:02028ee8  (20 bytes)
 *
 * Original:
 *   ldr  r0, [r0, r1, lsl #2]  ; r0 = table[index]
 *   cmn  r0, #1                ; compare with 0xffffffff
 *   movne r0, #1
 *   moveq r0, #0
 *   bx   lr
 *
 * Returns 1 when the 32-bit entry is not 0xffffffff (the table's "empty" mark),
 * else 0. Table meaning is unknown.
 */
unsigned int pvz_02028ee8_leaf(const unsigned int *table, unsigned int index)
{
    return table[index] != 0xffffffffu;
}
