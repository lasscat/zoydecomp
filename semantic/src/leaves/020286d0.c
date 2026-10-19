/* Clear a record: three zeroed words at +0,+4,+8, then a zero halfword at +0xc.
 * The halfword clear is written first in the source; this compiler emits the
 * widened word clears before the narrow halfword store. */
struct rec_b {
    int field0;      /* +0x0 */
    int field4;      /* +0x4 */
    int field8;      /* +0x8 */
    short fieldc;    /* +0xc */
};

void rec_b_clear(struct rec_b *p)
{
    p->fieldc = 0;
    p->field0 = 0;
    p->field4 = 0;
    p->field8 = 0;
}
