/* Address of element `index` in a table of 0x30-byte entries reached through
 * the fixed global record at 0x0210377c (base word at +0x08). */
struct UnknownEntryTable {
    unsigned int unknown_0x00;
    unsigned int unknown_0x04;
    unsigned char *entries_0x08;
};

unsigned char *pvz_0202b570_entry(int index)
{
    struct UnknownEntryTable *table = (struct UnknownEntryTable *)0x0210377c;

    return table->entries_0x08 + index * 0x30;
}
