/* Mechanical getter candidate; record identity and meaning are unknown. */
struct UnknownRecord038 {
    unsigned char unknown_padding_0x00_0x37[0x38];
    unsigned int field_0x38;
};

unsigned int pvz_02039914_get_field_0x38(struct UnknownRecord038 *record)
{
    return record->field_0x38;
}
