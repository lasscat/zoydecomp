/*
 * arm9:020014a8  (36 bytes)
 *
 * Original:
 *   cmp   r2, #0
 *   orrlt r1, r1, #0xc0        ; negative delta -> value |= 0xc0
 *   strhlt r1, [r0]            ; record[0x00] = value
 *   rsblt r1, r2, #0           ; r1 = -delta
 *   strhlt r1, [r0, #4]        ; record[0x04] = -delta
 *   orrge r1, r1, #0x80        ; non-negative delta -> value |= 0x80
 *   strhge r1, [r0]            ; record[0x00] = value
 *   strhge r2, [r0, #4]        ; record[0x04] = delta
 *   bx    lr
 *
 * Stores a 16-bit tagged value plus a 16-bit signed magnitude at +0x04, with a
 * direction bit (0x40) folded into the tag for negative deltas and 0x80 always
 * set. Record identity and the meaning of the tag bits are unknown; only the
 * observed DS effect is modelled.
 */

struct TaggedDelta {
    unsigned short tag;         /* +0x00 */
    unsigned short unknown_02;  /* +0x02 */
    unsigned short magnitude;   /* +0x04 */
};

void pvz_020014a8_leaf(struct TaggedDelta *record, unsigned short tag, short delta)
{
    if (delta < 0) {
        record->tag = (unsigned short)(tag | 0xc0u);
        record->magnitude = (unsigned short)-delta;
    } else {
        record->tag = (unsigned short)(tag | 0x80u);
        record->magnitude = (unsigned short)delta;
    }
}
