/* Stores a byte into record+0x43. */
struct UnknownRecord {
    unsigned char unknown_0x00_0x42[0x43];
    unsigned char field_0x43;
};

void pvz_02039954_leaf(struct UnknownRecord *record, unsigned char value)
{
    record->field_0x43 = value;
}
