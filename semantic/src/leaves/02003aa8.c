/* Reads the 16-bit field at +0x0e of the fixed global record at 0x020fd340.
 * The record identity is unknown; the address comes from the original's
 * constant pool (the pool word sits just past the reviewed function extent). */
struct UnknownGlobalRecord {
    unsigned char before_0x0e[0x0e];
    unsigned short field_0x0e;
};

unsigned short pvz_02003aa8_get_field_0x0e(void)
{
    struct UnknownGlobalRecord *record = (struct UnknownGlobalRecord *)0x020fd340;

    return record->field_0x0e;
}
