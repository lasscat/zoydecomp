/* Sets bit `bit` in the flag byte array that starts 0x400 bytes into the
 * sub-record at +0x214 (the original builds the base as record+0x214 and then
 * adds 0x400). */
struct UnknownFlagBlock {
    unsigned char unknown_0x00_0x3ff[0x400];
    unsigned char flags_0x400[];
};

struct UnknownRecord {
    unsigned char unknown_0x00_0x213[0x214];
    struct UnknownFlagBlock flags_0x214;
};

void pvz_02097d08_set_flag(struct UnknownRecord *record, unsigned int bit)
{
    unsigned char *byte = &record->flags_0x214.flags_0x400[bit >> 3];

    *byte = (unsigned char)(*byte | (1u << (bit & 7)));
}
