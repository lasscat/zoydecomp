/* arm9:02005384
 * Detach a doubly linked node. Field 0x10 is the "forward" link tested first,
 * field 0x14 is the "backward" link; owner 0x8c/0x88 hold the two ends.
 */
struct node {
    unsigned char pad[0x10];
    struct node *fwd;  /* +0x10 */
    struct node *back; /* +0x14 */
};

struct list_owner {
    unsigned char pad[0x88];
    struct node *end_b; /* +0x88 */
    struct node *end_a; /* +0x8c */
};

void pvz_02005384_leaf(struct list_owner *owner, struct node *n)
{
    struct node *fwd = n->fwd;
    struct node *back = n->back;

    if (fwd)
        fwd->back = back;
    else
        owner->end_a = back;
    if (back)
        back->fwd = fwd;
    else
        owner->end_b = fwd;
}
