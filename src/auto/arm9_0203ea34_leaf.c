/* 0203ea34 (arm9, 28 bytes)  -- NOT exact (tier X); closest-fit source
 *
 * Target (7 instructions, 28 bytes):
 *   ldr r3, [r1, #4]    ; r3 = n->next
 *   ldr r2, [r0]        ; r2 = *a
 *   str r3, [r2, #4]    ; (*a)->next = n->next
 *   ldr r2, [r0]        ; r2 = *a          (reloaded)
 *   ldr r0, [r1, #4]    ; r0 = n->next      (reloaded)
 *   str r2, [r0]        ; (n->next)->prev = *a
 *   bx  lr
 *
 * Unlink node n from a doubly linked list whose head pointer is *a
 * (a is the address of n's predecessor). Layout: prev at 0x0, next at 0x4.
 *
 * This candidate has the same size (28 bytes) and the same 7-instruction
 * shape as the target. The only differences are register-allocation choices
 * (the compiler assigns the first two loads to r2/r3 instead of r3/r2 and
 * the two reloads to r0/r1 instead of r2/r0): 5 of 7 words differ, above the
 * N threshold of 4, so this is reported as X.
 *
 * The `volatile next` field is what forces the compiler to reload n->next
 * instead of forwarding the value it just stored; without it the function
 * collapses to 6 instructions / 24 bytes.
 */
struct node {
    struct node *prev;          /* 0x0 */
    struct node *volatile next; /* 0x4 */
};

void pvz_0203ea34_leaf(struct node **a, struct node *n)
{
    struct node *h = *a;
    struct node *nn = n->next;
    h->next = nn;
    n->next->prev = *a;
}
