/*
 * arm9:02041634  (24 bytes; arm9:02042df0 has identical bytes)
 *
 * Original:
 *   mov  r2, #0
 *   add  r1, r0, #4
 *   str  r2, [r0]              ; anchor->first = 0
 *   str  r2, [r0, #4]          ; anchor->second = 0
 *   str  r1, [r0, #8]          ; anchor->link = &anchor->second
 *   bx   lr
 *
 * Initializes a three-word list anchor: two null pointers and a link to the
 * second slot.
 *
 * Note on the `volatile` qualifier: clang merges the two adjacent zero stores
 * into a single `stmib` (20 bytes) unless they are volatile. `volatile` here
 * only pins the three separate stores of the observed DS sequence; the anchor
 * is an ordinary object. Structure meaning is unknown.
 */

struct ListAnchor {
    unsigned int *first;              /* +0x00 */
    unsigned int *second;             /* +0x04 */
    unsigned int **volatile link;     /* +0x08 */
};

void pvz_02041634_leaf(struct ListAnchor *anchor)
{
    anchor->first = 0;
    anchor->second = 0;
    anchor->link = &anchor->second;
}
