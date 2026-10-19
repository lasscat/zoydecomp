/* Field meaning and the second ABI argument are unknown. */
struct UnknownRecord3A4 {
    unsigned char unknown_padding_0x00_0x3a3[0x3a4];
    unsigned char field_0x3a4;
};

void pvz_0205a254_set_field_0x3a4_to_one(struct UnknownRecord3A4 *record,
                                         unsigned int unknown_argument)
{
    (void)unknown_argument;
    record->field_0x3a4 = 1;
}
