/* Adds the node's own address into the offset word that follows it. */
struct node_020281f0 {
    int value;
    unsigned int offset;
};

void self_rebase_020281f0(struct node_020281f0 *node)
{
    node->offset += (unsigned int)node;
}
