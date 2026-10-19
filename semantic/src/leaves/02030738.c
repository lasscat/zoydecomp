/* Reads the word at +0x88 of the record pointed to by the fixed global pointer
 * stored at 0x02104240. */
struct UnknownOwner {
    unsigned char unknown_0x00_0x87[0x88];
    unsigned int field_0x88;
};

unsigned int pvz_02030738_get_field_0x88(void)
{
    struct UnknownOwner *owner = *(struct UnknownOwner **)0x02104240;

    return owner->field_0x88;
}
