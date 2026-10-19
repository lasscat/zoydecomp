/* Mechanical field transfer candidate; both record identities are unknown. */
struct UnknownSource00C {
    unsigned char unknown_padding_0x00_0x0b[0x0c];
    unsigned int field_0x0c;
};
struct UnknownDestination000 {
    unsigned int field_0x00;
};

void pvz_020435bc_copy_field_0x0c_to_0x00(struct UnknownDestination000 *destination,
                                          const struct UnknownSource00C *source)
{
    destination->field_0x00 = source->field_0x0c;
}
