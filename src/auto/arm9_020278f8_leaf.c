/* Detach a node from a doubly-linked list that is embedded in a byte pool.

   The node keeps the two list links of the entry it currently occupies at
   +0x00/+0x04, a 16-bit element count at +0x08 and the byte offset of its
   entry inside the pool at +0x0a.  "slot" is the node's entry in the pool:
   the entry holds a forward link at +0 (or 0 when the node is at the head)
   and a backward link at +4 (or 0 when the node is at the tail).  The
   neighbouring nodes store their own entry at the same byte offset inside
   themselves, so the offset has to be added to the neighbour pointer before
   writing through it.  The entry is cleared and the element count drops by
   one. */
struct list_pair {
    void *next;
    void *prev;
};

struct list_node {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short entry_offset;
};

void pvz_020278f8_leaf(struct list_node *node, char *pool)
{
    struct list_pair *slot = (struct list_pair *)(pool + node->entry_offset);
    void *next = slot->next;
    void *prev;

    if (next == 0)
        node->head = slot->prev;
    else
        *(void **)((char *)next + node->entry_offset + 4) = slot->prev;

    prev = slot->prev;
    if (prev == 0)
        node->tail = slot->next;
    else
        *(void **)((char *)prev + node->entry_offset) = slot->next;

    slot->next = 0;
    slot->prev = 0;
    node->count--;
}
