/* Adds the node's own address into the offset word that follows it. */
struct node_020281f0 {
    int value;
    unsigned int offset;
};

void pvz_020281f0_leaf(struct node_020281f0 *node) { node->offset += (unsigned int)node; }
