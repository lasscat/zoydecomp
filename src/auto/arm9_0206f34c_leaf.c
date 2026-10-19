/*
 * arm9:0206f34c  (20 bytes)
 *
 * Original:
 *   ldr  r2, [r0, #0x688]      ; r2 = owner->field_0x688 (table base pointer)
 *   mov  r0, #0x14
 *   add  r2, r2, #0x1dc        ; base += 0x1dc
 *   mla  r0, r1, r0, r2        ; r0 = index * 0x14 + base
 *   bx   lr
 *
 * Returns the address of the index-th 0x14-byte element of the table whose base
 * pointer lives at +0x688 of the owner record, offset by +0x1dc. Unknown layout.
 */
void *pvz_0206f34c_leaf(const void *owner, unsigned int index)
{
    unsigned int base = *(const unsigned int *)((const char *)owner + 0x688);

    return (void *)(base + 0x1dcu + index * 0x14u);
}
