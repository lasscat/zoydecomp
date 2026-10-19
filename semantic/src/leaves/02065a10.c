/* 02065a10 (arm9, 28 bytes)
 * add r0, r0, #0x5000
 * ldr r0, [r0, #0xae4]   ; r0 = *(u32*)((char*)p + 0x5ae4)
 * sub r0, r0, #2
 * cmp r0, #1
 * movls r0, #1           ; unsigned (r0 <= 1)
 * movhi r0, #0
 * bx lr
 *
 * Return 1 when the state word at offset 0x5ae4 of p, minus 2, is 0 or 1
 * (i.e. the state is 2 or 3); otherwise 0.
 *
 * NOT exact (tier X). The original computes the address as
 *   add r0, r0, #0x5000 ; ldr r0, [r0, #0xae4]
 * and materialises the boolean with conditional moves (sub/cmp/movls/movhi)
 * = 7 instructions / 28 bytes. clang instead forms the 0x5ae4 constant with
 * mov+orr and materialises the predicate with clz/lsr = 8 instructions /
 * 32 bytes. This candidate is the natural source; no source form found stops
 * clang from using mov+orr for the large offset.
 */
int f(void *p)
{
    unsigned int v = *(unsigned int *)((char *)p + 0x5ae4) - 2;
    return v <= 1;
}
