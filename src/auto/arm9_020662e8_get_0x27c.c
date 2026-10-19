/* Record identity and field meaning are unknown; argument 0 is ABI-preserved. */
struct UnknownRecord27C {
    unsigned char unknown_padding_0x00_0x27b[0x27c];
    unsigned int field_0x27c;
};

unsigned int
pvz_020662e8_get_field_0x27c_from_second_argument(const void *unknown_first_argument,
                                                  const struct UnknownRecord27C *record)
{
    (void)unknown_first_argument;
    return record->field_0x27c;
}
