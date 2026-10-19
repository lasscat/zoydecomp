/*
 * arm9:02042e08  (24 bytes)  -- tier N (same size, 4 differing instructions)
 *
 * Original instructions:
 *   mov  r2, #0
 *   add  r1, r0, #4
 *   str  r2, [r0]
 *   str  r2, [r0, #4]
 *   str  r1, [r0, #8]        ; *(u32 *)(self + 8) = self + 4
 *   bx   lr
 *
 * Zeroes the first two words and stores the record's own +0x04 address in the
 * word at +0x08 (an intrusive list header with a self sentinel).
 *
 * volatile is used only to keep the original's ascending store order; without
 * it clang folds the +0x04/+0x08 stores into stmib. The two emitters then still
 * disagree on register allocation: the original computes self+4 into r1 and the
 * zero into r2 before the stores, clang computes self+4 just before its use and
 * keeps the zero in r1.
 */
struct NodeHeader_02042e08 {
    volatile unsigned int field_0x00;  /* 0x00 */
    volatile unsigned int link_0x04;   /* 0x04 */
    volatile unsigned int link_0x08;   /* 0x08 */
};

void pvz_02042e08(struct NodeHeader_02042e08 *header)
{
    header->field_0x00 = 0;
    header->link_0x04 = 0;
    header->link_0x08 = (unsigned int)&header->link_0x04;
}
