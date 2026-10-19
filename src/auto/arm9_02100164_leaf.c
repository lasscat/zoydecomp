/* arm9:02100164  (60 bytes, no literal pool)
 *
 *   push {r4, lr}
 *   ldr  r3, [r0, #4]
 *   ldr  r2, [r1, #4]
 *   ldr  ip, [r0]
 *   smull r4, lr, r3, r2    ; a[1] * b[1]
 *   ldr  r2, [r1]
 *   ldr  r3, [r0, #8]
 *   smlal r4, lr, ip, r2    ; + a[0] * b[0]
 *   ldr  r0, [r1, #8]
 *   smlal r4, lr, r3, r0    ; + a[2] * b[2]
 *   adds r0, r4, #0x800
 *   adc  r1, lr, #0
 *   lsr  r0, r0, #0xc
 *   orr  r0, r0, r1, lsl #20
 *   pop  {r4, pc}
 *
 * Fixed-point dot product of two 3-element vectors: the 64-bit sum is rounded
 * with 0x800 and shifted down by 12, keeping the low 32 bits of the result.
 * The product order is written left to right (a[0], a[1], a[2]); the backend
 * is the one that starts with a[1] * b[1] and folds the 0x800 into `adds`/`adc`
 * exactly as the original does.  Exact byte match.
 */
int pvz_02100164_leaf(const int *a, const int *b)
{
    long long sum = (long long)a[0] * b[0] + (long long)a[1] * b[1] + (long long)a[2] * b[2];

    return (int)((sum + 0x800) >> 12);
}
