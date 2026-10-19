/* Record identity and field meaning are unknown; argument 0 is ABI-preserved. */
struct UnknownRecord16C {
    unsigned char unknown_padding_0x00_0x16b[0x16c];
    unsigned int field_0x16c;
};

unsigned int
pvz_0206ee84_get_field_0x16c_from_second_argument(const void *unknown_first_argument,
                                                  const struct UnknownRecord16C *record)
{
    (void)unknown_first_argument;
    return record->field_0x16c;
}
