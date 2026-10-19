/* Initialises a record: the fixed table/entry word at 0x020e825c goes into
 * +0x00, then +0x08, +0x0c and +0x10 are cleared and the byte at +0x14 is
 * zeroed.  The word at +0x04 is left untouched by the original. */
struct UnknownRecord {
    unsigned int link_0x00;
    unsigned int unknown_0x04;
    unsigned int unknown_0x08;
    unsigned int unknown_0x0c;
    unsigned int unknown_0x10;
    unsigned char unknown_0x14;
};

void pvz_0209191c_init(struct UnknownRecord *record)
{
    record->link_0x00 = 0x020e825c;
    record->unknown_0x08 = 0;
    record->unknown_0x0c = 0;
    record->unknown_0x10 = 0;
    record->unknown_0x14 = 0;
}
