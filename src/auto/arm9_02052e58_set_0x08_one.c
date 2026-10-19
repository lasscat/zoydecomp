/* Field meaning and the second ABI argument are unknown. */
struct UnknownRecord008 {
    unsigned char unknown_padding_0x00_0x07[0x08];
    unsigned char field_0x08;
};

void pvz_02052e58_set_field_0x08_to_one(struct UnknownRecord008 *record,
                                        unsigned int unknown_argument)
{
    (void)unknown_argument;
    record->field_0x08 = 1;
}
