/* Initialises a list holder: flag cleared, both links point at the embedded
   node (the node lives at offset 4).  The pointer is volatile so the original's
   store order (flag, then prev at +8, then next at +4) is kept. */
struct Link {
    struct Link *next;
    struct Link *prev;
};

struct Holder {
    unsigned flag;
    struct Link node;
};

void init_holder(volatile struct Holder *p)
{
    p->flag = 0;
    p->node.prev = (struct Link *)(void *)&p->node;
    p->node.next = (struct Link *)(void *)&p->node;
}
