/* The word at 0x02104240 points at a root object; the word at offset 0x90 of
   that root points at a table of 16-byte entries. Returns the value word
   (offset 0x0c) of entry 'index', or zero when index is out of range. */
struct entry_020305a8 {
    unsigned int type;
    unsigned int pad;
    unsigned int count;
    unsigned int value;
};

struct root_020305a8 {
    unsigned char pad[0x90];
    void *table;
};

unsigned int lookup_020305a8(unsigned int index)
{
    struct root_020305a8 *root = *(struct root_020305a8 **)0x02104240;
    struct entry_020305a8 *list = (struct entry_020305a8 *)root->table;
    if (index >= list->count)
        return 0;
    return list[index].value;
}
