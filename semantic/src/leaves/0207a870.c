/* Reads the word pointed to by element `index` of the 0x2c-byte global entry
 * table at 0x020e680c, through the entry's +0x04 pointer; zero when the entry
 * has no pointer. */
struct UnknownEntry {
    unsigned char unknown_0x00_0x03[4];
    unsigned int *value_0x04;
    unsigned char unknown_0x08_0x2b[0x24];
};

unsigned int pvz_0207a870_get_value(int index)
{
    struct UnknownEntry *entry = (struct UnknownEntry *)(0x020e680c + index * 0x2c);

    if (entry->value_0x04 != 0) {
        return *entry->value_0x04;
    }
    return 0;
}
