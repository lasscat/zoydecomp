/* Copies the three payload words of the source node and stamps the target's
   first word with the constant tag 0x020e1640 (a vtable/type word). */
struct node_02046670 {
    unsigned int tag;
    unsigned int field4;
    unsigned int field8;
    unsigned int fieldc;
};

void copy_node_02046670(struct node_02046670 *dst, const struct node_02046670 *src)
{
    dst->tag = 0x020e1640;
    dst->field4 = src->field4;
    dst->field8 = src->field8;
    dst->fieldc = src->fieldc;
}
