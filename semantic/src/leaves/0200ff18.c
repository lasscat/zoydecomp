/* Stores a value into element `index` of a table reached through the fixed
 * global record at 0x020fffec: the table base is its +0x04 word and each
 * element is 4 bytes, with the value placed at element offset 0x18. */
struct UnknownTableHolder {
    unsigned int unknown_0x00;
    unsigned char *table_0x04;
};

void pvz_0200ff18_store_element(int index, int value)
{
    struct UnknownTableHolder *holder = (struct UnknownTableHolder *)0x020fffec;

    *(int *)(holder->table_0x04 + index * 4 + 0x18) = value;
}
