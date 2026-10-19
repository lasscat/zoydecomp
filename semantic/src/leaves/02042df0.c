/*
 * arm9:02042df0  (24 bytes; byte-identical to arm9:02041634)
 *
 * Original:
 *   mov  r2, #0
 *   add  r1, r0, #4
 *   str  r2, [r0]
 *   str  r2, [r0, #4]
 *   str  r1, [r0, #8]
 *   bx   lr
 *
 * Same three-word list-anchor initialization as 0x02041634; the two addresses
 * share one target hash, so the same source is used.
 *
 * Note on the `volatile` qualifier: it only pins the three separate stores of
 * the observed DS sequence against clang's `stmib` store merging. Structure
 * meaning is unknown.
 */

struct ListAnchor {
    unsigned int *first;              /* +0x00 */
    unsigned int *second;             /* +0x04 */
    unsigned int **volatile link;     /* +0x08 */
};

void pvz_02042df0_leaf(struct ListAnchor *anchor)
{
    anchor->first = 0;
    anchor->second = 0;
    anchor->link = &anchor->second;
}
