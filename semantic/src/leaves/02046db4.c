/* Link two neighbouring doubly linked list nodes.
 *
 * Node layout: prev at +0, next at +4.
 *   x = *a;            (x is the first argument's target node)
 *   y = b[1];          (b[1] is the "next" field of the second argument)
 *   x->next = y;
 *   y->prev = x;
 *
 * The target re-reads both *a and b[1] for the second store (it does not keep
 * either value in a register across the first store), so the pointer targets
 * are read through volatile-qualified pointer-to-pointer arguments.  This
 * reproduces the same 7-instruction shape; the remaining difference is only
 * which physical registers the compiler assigns (target r3/r2 vs candidate
 * r2/r3), which the byte comparator counts as differences.
 */
typedef struct node {
    struct node *prev;   /* +0x0 */
    struct node *next;   /* +0x4 */
} node;

void list_link(node *volatile *a, node *volatile *b)
{
    (*a)->next = b[1];
    b[1]->prev = *a;
}
