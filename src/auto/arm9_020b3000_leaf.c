/*
 * arm9:020b3000  (24 bytes)
 *
 * Original:
 *   ldr  r3, [r0, #0xc]        ; r3 = buffer->used
 *   ldr  r2, [r0, #8]          ; r2 = buffer->capacity
 *   add  r1, r3, r1            ; r1 = used + size
 *   cmp  r1, r2
 *   strls r1, [r0, #0xc]       ; if (used + size <= capacity) used = used + size
 *   bx   lr
 *
 * Bounded consumption/advance: the counter at +0x0c grows by `size` only while
 * it stays within the limit at +0x08. Field meanings are unknown.
 */
void pvz_020b3000_leaf(void *buffer, unsigned int size)
{
    unsigned int used = *(unsigned int *)((char *)buffer + 0x0c);
    unsigned int capacity = *(unsigned int *)((char *)buffer + 0x08);
    unsigned int next = used + size;

    if (next <= capacity) {
        *(unsigned int *)((char *)buffer + 0x0c) = next;
    }
}
