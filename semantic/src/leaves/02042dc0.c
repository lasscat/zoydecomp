/* Initialises a list owner: a zero word at +0x00 and a circular list node at
 * +0x04 whose two links both point back at themselves. */
struct UnknownListNode {
    struct UnknownListNode *back_0x00;
    struct UnknownListNode *forward_0x04;
};

struct UnknownListOwner {
    unsigned int count_0x00;
    struct UnknownListNode node_0x04;
};

void pvz_02042dc0_init_list(struct UnknownListOwner *owner)
{
    struct UnknownListNode *node = &owner->node_0x04;

    owner->count_0x00 = 0;
    node->forward_0x04 = node;
    owner->node_0x04.back_0x00 = node;
}
