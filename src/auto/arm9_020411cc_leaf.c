/* Reports whether record+0x14 is non-zero. */
struct UnknownRecord {
    unsigned char unknown_0x00_0x13[0x14];
    unsigned int field_0x14;
};

int pvz_020411cc_leaf(struct UnknownRecord *record) { return record->field_0x14 != 0; }
