/* Walk a singly linked list and publish the shared value to every node, then to
 * the owner.  Layout (unknown):
 *   p + 0x1c : value, p + 0x28 : cached value, p + 0x2c : list head
 *   node + 0x08 : value slot, node + 0x0c : next pointer
 * p + 0x1c is documented volatile so that it is re-read for each node and again
 * for the owner, matching the original's independent reloads.
 */
void sub_02027bb8(unsigned char *p)
{
    unsigned char *node = *(unsigned char **)(p + 0x2c);

    while (node != 0) {
        *(unsigned int *)(node + 8) = *(volatile unsigned int *)(p + 0x1c);
        node = *(unsigned char **)(node + 0xc);
    }
    *(unsigned int *)(p + 0x28) = *(volatile unsigned int *)(p + 0x1c);
}
