/* Stores two words into the 0x8c-byte element `index` of the two parallel
 * global tables at 0x02105d84 and 0x02105d88. */
void pvz_02034f08_set_element(int index, unsigned int first, unsigned int second)
{
    unsigned int offset = index * 0x8c;

    *(unsigned int *)(0x02105d84 + offset) = first;
    *(unsigned int *)(0x02105d88 + offset) = second;
}
