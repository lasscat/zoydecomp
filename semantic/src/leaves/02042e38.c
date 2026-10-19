/* arm9:02042e38
 * Initialises a 4-word record: words +0 and +4 are cleared and the word at
 * +0xc points at the field at +4; the word at +8 is left untouched.
 */
struct record4 {
    unsigned int first;   /* +0x0 */
    unsigned int second;  /* +0x4 */
    unsigned int spare;   /* +0x8, untouched */
    unsigned int link;    /* +0xc */
};

void init_record4(struct record4 *record)
{
    record->first = 0;
    record->second = 0;
    record->link = (unsigned int)((char *)record + 4);
}
