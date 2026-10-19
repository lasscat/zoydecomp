/*
 * arm9:0203964c  (24 bytes)  -- tier N (same size, 4 differing instructions)
 *
 * Original instructions:
 *   add  r1, r0, #4
 *   mov  r2, #0
 *   str  r2, [r0]            ; count = 0
 *   str  r1, [r1, #4]        ; *(u32 *)(self + 8) = self + 4
 *   str  r1, [r0, #4]        ; *(u32 *)(self + 4) = self + 4
 *   bx   lr
 *
 * Initialises an intrusive list header: zeroes the count and points both link
 * fields at the embedded link slot at +0x04, i.e. an empty list whose sentinel
 * is the header itself. The two sentinel stores share one address register
 * (self + 4) and are emitted in the order +0x08 then +0x04.
 *
 * volatile is used only to keep that store order: without it clang merges the
 * +0x00/+0x04 stores into a single stm and gives a 20-byte candidate. With it
 * clang emits six instructions like the original but materialises the sentinel
 * late (after the first store) and reuses r1 for both the zero and the
 * sentinel, where the original materialises the sentinel first into r1 and the
 * zero into r2.
 */
struct ListHeader_0203964c {
    volatile unsigned int count;      /* 0x00 */
    volatile unsigned int link_0x04;  /* 0x04 */
    volatile unsigned int link_0x08;  /* 0x08 */
};

void pvz_0203964c(struct ListHeader_0203964c *header)
{
    unsigned int sentinel = (unsigned int)&header->link_0x04;

    header->count = 0;
    header->link_0x08 = sentinel;
    header->link_0x04 = sentinel;
}
