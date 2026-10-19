/* Initialize a 12-byte record and store the caller's halfword at +0xa.
 *
 * Layout inferred from the target stores: cleared word +0, cleared word +4,
 * cleared halfword +8, caller halfword +0xa.
 *
 * The record is treated as a volatile hardware register block: the target
 * stores every field in strictly increasing offset order and keeps the argument
 * live in r1 while zero is materialized in r2.  Without volatile this compiler
 * hoists the argument halfword store to the front and reuses r1 for zero,
 * reordering all four stores.  Volatile forces program order; the emitted
 * opcodes are identical plain str/strh stores.
 */
struct rec_a {
    int field0;      /* +0x0 */
    int field4;      /* +0x4 */
    short field8;    /* +0x8 */
    short fielda;    /* +0xa */
};

void rec_a_init(volatile struct rec_a *p, short value)
{
    p->field0 = 0;
    p->field4 = 0;
    p->field8 = 0;
    p->fielda = value;
}
