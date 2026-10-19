/* 020280c8 (24 bytes): bounded lookup into an array of 8-byte records.
 *   ldrh   r2, [r0]           ; r2 = table->count (u16 at offset 0)
 *   cmp    r1, r2
 *   ldrlo  r0, [r0, #4]       ; r0 = table->array (u32 at offset 4), when in range
 *   addlo  r0, r0, r1, lsl #3 ; r0 += index * 8
 *   movhs  r0, #0             ; out of range -> 0
 *   bx     lr
 * Offsets: +0x0 unsigned short count, +0x4 unsigned int array_base.
 * Element stride is 8 bytes; the result is the byte address of record index. */
typedef struct
{
    unsigned short count; /* +0x0 */
    unsigned short pad;   /* +0x2 */
    unsigned int array;   /* +0x4 */
} leaf_table;

unsigned int leaf_lookup(leaf_table *table, unsigned int index)
{
    unsigned int result = table->array + index * 8;
    if (index >= table->count)
        result = 0;
    return result;
}
