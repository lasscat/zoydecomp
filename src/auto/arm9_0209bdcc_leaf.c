/* arm9:0209bdcc  (92 bytes = 88 code + 4 byte pool)
 *
 *   ldr  r1, [pc, #0x50]    ; -> 0x021069f4, pool word inside the extent
 *   mov  r2, #0
 *   ldr  r1, [r1]
 *   mov  r3, r2
 *   str  r1, [r0, #0x188]   ; state = *global
 *   do { str r3,[r0,r2,lsl #2]; r2++; } while (r2 < 0x35);
 *   do { str ip,[r0+0xe4+r3*4]; r3++; } while (r3 < 4);
 *   do { str r2,[r0+0xf4+ip*4]; ip++; } while (ip < 0x25);
 *   bx   lr
 *
 * Clears the three tables of a 0x18c-byte game record and seeds the state
 * word at +0x188 from the global at 0x021069f4.  The tables are 0x35, 4 and
 * 0x25 words long and start at +0x00, +0xe4 and +0xf4.
 *
 * Each table is cleared by its own loop and the three loops each have their
 * own index variable; the original's index registers (r2, r3, ip) and its
 * "reuse the known-zero register" copies (the zero stored by one loop becomes
 * the index of the next) only come out that way with three separate counters
 * and do-while bodies.  Exact byte match.
 */
struct Ctx_0209bdcc {
    int table_a[0x35]; /* +0x000 */
    int gap_0xd4[4];   /* +0x0d4 */
    int table_b[4];    /* +0x0e4 */
    int table_c[0x25]; /* +0x0f4 */
    int state;         /* +0x188 */
};

void pvz_0209bdcc_leaf(struct Ctx_0209bdcc *ctx)
{
    int i, j, k;

    ctx->state = *(int *)0x021069f4;
    i = 0;
    do {
        ctx->table_a[i] = 0;
        i++;
    } while (i < 0x35);
    j = 0;
    do {
        ctx->table_b[j] = 0;
        j++;
    } while (j < 4);
    k = 0;
    do {
        ctx->table_c[k] = 0;
        k++;
    } while (k < 0x25);
}
