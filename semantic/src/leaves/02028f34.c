/* arm9:02028f34
 * Reports whether the 4-byte array element at index 2 of the table is in
 * use; a slot holding 0xFFFFFFFF counts as free.
 */
int is_slot_used(const unsigned int *table, int index)
{
    return table[index + 2] != 0xFFFFFFFFu;
}
