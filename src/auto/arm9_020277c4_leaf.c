/* arm9:020277c4  (44 bytes, no literal pool)
 *
 *   ldrh r3, [r0, #0xa]     ; stride
 *   mov  r2, #0
 *   add  ip, r1, r3         ; entry = slot + stride
 *   str  r2, [ip, #4]
 *   str  r2, [r1, r3]       ; clear the entry's two link words
 *   ldrh r2, [r0, #8]       ; usage counter, read here
 *   str  r1, [r0]           ; head
 *   str  r1, [r0, #4]       ; tail
 *   add  r1, r2, #1
 *   strh r1, [r0, #8]       ; usage counter + 1
 *   bx   lr
 *
 * Inserts a slot at the front of a pool: the pair of link words that sits
 * `stride` bytes into the slot is cleared, the pool head/tail become the slot
 * and the 16-bit usage counter is bumped.
 *
 * The counter has to be read between the two store groups (a local that is
 * assigned there, not at the top of the function) - that is what keeps the
 * load with operand r2 and the `add r1, r2, #1` at the end, exactly as the
 * original schedules them. Exact byte match.
 */
struct Pool_020277c4 {
    unsigned int first;    /* +0x00 */
    unsigned int second;   /* +0x04 */
    unsigned short count;  /* +0x08 */
    unsigned short stride; /* +0x0a */
};

void pvz_020277c4_leaf(struct Pool_020277c4 *pool, unsigned char *slot)
{
    unsigned char *entry = slot + pool->stride;
    unsigned short count;

    *(unsigned int *)(entry + 4) = 0;
    *(unsigned int *)entry = 0;
    count = pool->count;
    pool->first = (unsigned int)slot;
    pool->second = (unsigned int)slot;
    pool->count = (unsigned short)(count + 1);
}
