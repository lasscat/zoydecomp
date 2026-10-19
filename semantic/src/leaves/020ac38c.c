/* Initialises a record from the word of the fixed global at 0x021069f4:
 * that word goes to +0x00, then +0x04, +0x08 and the byte at +0x0c are
 * cleared. */
struct UnknownRecord {
    unsigned int source_0x00;
    unsigned int unknown_0x04;
    unsigned int unknown_0x08;
    unsigned char unknown_0x0c;
};

void pvz_020ac38c_init(struct UnknownRecord *record)
{
    unsigned int value = *(unsigned int *)0x021069f4;

    record->source_0x00 = value;
    record->unknown_0x04 = 0;
    record->unknown_0x08 = 0;
    record->unknown_0x0c = 0;
}
