/* arm9:02005128  (36 bytes, no literal pool)
 *
 *   ldr  r1, [r0, #0xc]     ; tail word
 *   mov  r2, #0
 *   and  r1, r1, #0xff000000
 *   bic  r1, r1, #0xff000000
 *   str  r2, [r0, #4]
 *   str  r2, [r0]
 *   str  r2, [r0, #8]
 *   str  r1, [r0, #0xc]
 *   bx   lr
 *
 * Resets the record completely: the three leading words and the last word.
 * The last word is covered by two bit fields (24 bits, then the top 8 bits),
 * so clearing both masks the reloaded word down to nothing; this value effect
 * is what produces the `and` immediately followed by the `bic`.
 *
 * Tier X: size and instruction content match (the original also has one load,
 * one 0.0 materialisation, both mask ops and four stores), but this compiler
 * keeps the zero in r1 and the masked word in r2 and emits the load/mask pair
 * after the three zero stores, whereas the original materialises the zero in
 * r2, keeps the masked word in r1 and hoists the load/mask pair above the
 * stores - five instruction positions differ.  A single load plus two mask
 * constants in one expression is not a way out: the backend folds
 * `(x & 0xff000000) & 0x00ffffff` to zero and drops the load, so the two
 * separate field updates are the faithful description.
 */
struct Node_02005128 {
    unsigned int field_0x00;
    unsigned int field_0x04;
    unsigned int field_0x08;
    unsigned int low : 24;
    unsigned int high : 8;
};

void pvz_02005128_reset(struct Node_02005128 *node)
{
    node->field_0x00 = 0;
    node->field_0x04 = 0;
    node->field_0x08 = 0;
    node->low = 0;
    node->high = 0;
}
