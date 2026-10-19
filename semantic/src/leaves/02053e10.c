/*
 * arm9:02053e10  (16 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r2, [pc, #8]          ; r2 = 0x020d4b98 (table base)
 *   mov  r1, #0x1c
 *   mla  r0, r1, r0, r2        ; r0 = index * 0x1c + base
 *   bx   lr
 *
 * Returns the address of the index-th 0x1c-byte element of the table at
 * 0x020d4b98. Table meaning is unknown.
 */
void *pvz_02053e10_leaf(unsigned int index)
{
    return (void *)(0x020d4b98u + index * 0x1cu);
}
