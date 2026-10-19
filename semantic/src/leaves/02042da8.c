/* Builds a node whose third field points at its own second field.  The pointer
   is volatile so the original's three independent stores are kept instead of a
   merged block store. */
struct Node {
    unsigned a;
    unsigned b;
    void *c;
};

void init_node(volatile struct Node *p)
{
    p->a = 0;
    p->b = 0;
    p->c = (void *)&p->b;
}
