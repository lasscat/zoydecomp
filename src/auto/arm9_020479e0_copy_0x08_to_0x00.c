/* Mechanical field transfer candidate; both record identities are unknown. */
struct UnknownSource008 {
    unsigned char unknown_padding_0x00_0x07[0x08];
    unsigned int field_0x08;
};
struct UnknownDestination000 {
    unsigned int field_0x00;
};

void pvz_020479e0_copy_field_0x08_to_0x00(struct UnknownDestination000 *destination,
                                          const struct UnknownSource008 *source)
{
    destination->field_0x00 = source->field_0x08;
}
