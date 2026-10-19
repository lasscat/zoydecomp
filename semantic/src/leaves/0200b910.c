/*
 * arm9:0200b910  (8 bytes)
 *
 * Original:
 *   ldr  r0, [r0, #0x24]
 *   bx   lr
 *
 * Returns the 32-bit word at +0x24 of the record. Field meaning is unknown.
 */
unsigned int pvz_0200b910_leaf(const void *record)
{
    return *(const unsigned int *)((const char *)record + 0x24);
}
