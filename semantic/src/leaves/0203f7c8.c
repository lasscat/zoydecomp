/* arm9:0203f7c8  (44 bytes, no literal pool)
 *
 *   mov  r2, #0
 *   mov  r1, #0x3f800000    ; 1.0f
 *   str  r2, [r0, #0x1c]
 *   str  r2, [r0, #0x18]
 *   str  r2, [r0, #0x14]
 *   str  r2, [r0, #0x0c]
 *   str  r2, [r0, #8]
 *   str  r1, [r0, #0x20]
 *   str  r1, [r0, #0x10]
 *   stm  r0, {r1, r2}       ; [0x00] = 1.0f, [0x04] = 0
 *   bx   lr
 *
 * Writes the 3x3 identity matrix over nine floats: the three diagonal slots
 * (0x00, 0x10, 0x20) get 1.0f and the other six get 0.0f.  The original emits
 * the zero slots in decreasing offset order, then the two single-word 1.0f
 * slots, and finishes with the adjacent slot pair merged into one stm.
 *
 * Tier X: the size (44 bytes), the whole instruction sequence and the stm at
 * the end are matched, but this compiler materialises the 1.0f constant
 * immediately before its first use (slot 7 of 11) instead of hoisting it next
 * to the 0.0f constant at the top, which shifts five instruction positions.
 * Chained assignments for the two groups of slots (a single statement per
 * value) are what bring the schedule closest to the original; the draft
 * variants with nine plain stores came out ascending order and 48 bytes.
 */
void pvz_0203f7c8_identity(float *m)
{
    m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
    m[0] = m[4] = m[8] = 1.0f;
    m[1] = 0.0f;
}
