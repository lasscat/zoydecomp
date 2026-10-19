/* 0203be48 (24 bytes): initialize a small intrusive structure.
 *   mov  r2, #0
 *   add  r1, r0, #4
 *   str  r2, [r0]        ; field @0x0 = 0
 *   str  r2, [r0, #4]    ; field @0x4 = 0
 *   str  r1, [r0, #0xc]  ; field @0xc = self + 4  (points at field @0x4)
 *   bx   lr
 * Field @0x8 is left untouched. */
typedef struct
{
    unsigned int zero0;  /* +0x0 */
    unsigned int zero4;  /* +0x4 */
    unsigned int keep8;  /* +0x8  untouched */
    void *link12;        /* +0xc */
} leaf_node_c;

void leaf_init_c(leaf_node_c *node)
{
    node->zero0 = 0;
    node->zero4 = 0;
    node->link12 = &node->zero4;
}
