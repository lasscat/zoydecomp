/* arm9:020305d0
 * Bounds-checked accessor for a 16-byte-stride table.
 * The global at 0x02104240 points at a manager object; the word at +0x90 of
 * that object points at the table, whose element count is the 32-bit word at
 * +8.  Elements are 16 bytes each, the first one at +0x10.
 * Returns 0 when index is out of range (unsigned comparison).
 */
unsigned int get_table_entry(unsigned int index)
{
    unsigned char *manager = *(unsigned char **)0x02104240u;
    unsigned char *table = *(unsigned char **)(manager + 0x90);

    if (index >= *(unsigned int *)(table + 8))
        return 0;

    return *(unsigned int *)(table + 0x10 + index * 16u);
}
