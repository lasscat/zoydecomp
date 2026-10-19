/*
 * arm9:02097bb0  (24 bytes)
 *
 *   ldr  r1, [r0, #0x5e8]
 *   ldr  r0, [pc, #0xc]      ; literal 2500
 *   cmp  r1, r0
 *   movge r0, #1
 *   movlt r0, #0
 *   bx   lr
 *
 * Signed comparison: reports whether the 32-bit counter at +0x5e8 has
 * reached 2500. The original loads the threshold from a literal pool,
 * clang materialises it with movw.
 */
struct Counter_02097bb0 {
    unsigned char pad_0x00[0x5e8];
    int counter_0x5e8;
};

int pvz_02097bb0(struct Counter_02097bb0 *state)
{
    return state->counter_0x5e8 >= 2500;
}
