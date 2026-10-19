/* 02027970 (arm9, 20 bytes)  -- EXACT byte match with clang23-arm946-o2
 *
 * Target:
 *   cmp    r1, #0
 *   ldreq  r0, [r0, #4]      ; if q == 0: r0 = *(u32 *)((char *)p + 4)
 *   ldrhne r0, [r0, #0xa]    ; else:      r0 = *(u16 *)((char *)p + 0xa)
 *   ldrne  r0, [r1, r0]      ; else:      r0 = *(u32 *)((char *)q + r0)
 *   bx     lr
 *
 * If q is null, return the word at offset 4 of p. Otherwise treat the
 * halfword at offset 0xa of p as a byte offset into q and return that word.
 *
 * NOTE: the loads from p are declared volatile. With plain loads the
 * compiler commoned the two branch results into one unconditional load
 * (6 instructions / 24 bytes) instead of two predicated loads. The volatile
 * qualifier reproduces the original compiler's separate predicated loads;
 * it does not alter the memory being read.
 * Field offsets: p+0x4 unknown word, p+0xa unknown halfword byte offset.
 */
unsigned int f(volatile unsigned char *p, unsigned char *q)
{
    if (q == 0)
        return *(volatile unsigned int *)(p + 4);
    return *(unsigned int *)(q + *(volatile unsigned short *)(p + 10));
}
