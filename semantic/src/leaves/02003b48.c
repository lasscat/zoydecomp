/* Reads the 16-bit field at +0x18 of the fixed global record at 0x020fd340
 * (same record as pvz_02003aa8_get_field_0x0e).  Identity unknown. */
struct UnknownGlobalRecord {
    unsigned char before_0x18[0x18];
    unsigned short field_0x18;
};

unsigned short pvz_02003b48_get_field_0x18(void)
{
    struct UnknownGlobalRecord *record = (struct UnknownGlobalRecord *)0x020fd340;

    return record->field_0x18;
}
