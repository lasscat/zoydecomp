/* 020411b4 (24 bytes): initialize a small intrusive structure.
 *   mov  r2, #0
 *   add  r1, r0, #4
 *   str  r2, [r0]        ; field @0x0 = 0
 *   str  r2, [r0, #4]    ; field @0x4 = 0
 *   str  r1, [r0, #8]    ; field @0x8 = self + 4  (points at field @0x4)
 *   bx   lr
 * Field @0xc is left untouched. The three independent stores are what the
 * target emits, so the object is modelled as volatile to keep them separate
 * and in order (otherwise a compiler merges them into an STMIB). */
typedef struct
{
    unsigned int zero0;  /* +0x0 */
    unsigned int zero4;  /* +0x4 */
    void *link8;         /* +0x8 */
    unsigned int keep12; /* +0xc  untouched */
} leaf_node_d;

void leaf_init_d(volatile leaf_node_d *node)
{
    node->zero0 = 0;
    node->zero4 = 0;
    node->link8 = (void *)&node->zero4;
}
