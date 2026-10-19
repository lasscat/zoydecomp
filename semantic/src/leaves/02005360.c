/* Pushes a node onto a doubly linked list kept inside an owner record.
 * The list head lives at owner+0x8c and the "last pushed" slot at owner+0x88;
 * a node links backwards through +0x10 and forwards through +0x14.
 * With an empty list the node address is recorded at +0x88, otherwise it is
 * written into the old head's back link.  The node is then linked to the old
 * head, its back link cleared, and the new head published last. */
struct UnknownNode {
    unsigned char unknown_0x00_0x0f[0x10];
    struct UnknownNode *back_0x10;
    struct UnknownNode *forward_0x14;
};

struct UnknownOwner {
    unsigned char unknown_0x00_0x87[0x88];
    struct UnknownNode *last_0x88;
    struct UnknownNode *head_0x8c;
};

void pvz_02005360_push_front(struct UnknownOwner *owner, struct UnknownNode *node)
{
    struct UnknownNode *head = owner->head_0x8c;

    if (head == 0) {
        owner->last_0x88 = node;
    } else {
        head->back_0x10 = node;
    }
    node->forward_0x14 = head;
    node->back_0x10 = 0;
    owner->head_0x8c = node;
}
