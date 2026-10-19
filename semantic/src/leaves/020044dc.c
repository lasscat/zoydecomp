/* Removes the head node of a doubly linked list and returns it
 * (single-exit form). */
struct node {
    char pad_00[0x78];
    int field_78;
    struct node *prev; /* 0x7c */
    struct node *next; /* 0x80 */
};

struct list {
    struct node *head; /* 0x00 */
    struct node *tail; /* 0x04 */
};

struct node *list_pop_front(struct list *l)
{
    struct node *n = l->head;
    if (n != 0) {
        struct node *next = n->next;
        l->head = next;
        if (next != 0) {
            next->prev = 0;
        } else {
            l->tail = 0;
            n->field_78 = 0;
        }
    }
    return n;
}
