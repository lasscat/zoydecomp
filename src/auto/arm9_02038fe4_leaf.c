/* arm9:02038fe4  (48 bytes, no literal pool)
 *
 *   ldr  r3, [r0]
 *   ldr  r2, [r1]
 *   cmp  r3, r2
 *   ldreq r3, [r0, #4]
 *   ldreq r2, [r1, #4]
 *   cmpeq r3, r2
 *   ldreq r2, [r0, #8]
 *   ldreq r0, [r1, #8]
 *   cmpeq r2, r0
 *   moveq r0, #1
 *   movne r0, #0
 *   bx   lr
 *
 * Three-word equality test; short circuit keeps the later loads conditional.
 */
int pvz_02038fe4_leaf(const unsigned int *a, const unsigned int *b)
{
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}
