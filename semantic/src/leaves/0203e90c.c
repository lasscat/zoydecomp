/* Clear a record: two zeroed words at +0,+4 and a zero byte at +8.
 * The byte clear is written first in the source; this compiler emits the
 * widened word clears before the narrow byte store. */
struct rec_c {
    int field0;      /* +0x0 */
    int field4;      /* +0x4 */
    char field8;     /* +0x8 */
};

void rec_c_clear(struct rec_c *p)
{
    p->field8 = 0;
    p->field0 = 0;
    p->field4 = 0;
}
