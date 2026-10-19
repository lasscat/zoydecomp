/* arm9:02067a2c
 * Zero-initialises a seven-word record, except the word at +0x14 which is
 * set to 1 (stored in ascending field order like the original).
 */
struct record7 {
    unsigned int word0;   /* +0x00 */
    unsigned int word1;   /* +0x04 */
    unsigned int word2;   /* +0x08 */
    unsigned int word3;   /* +0x0c */
    unsigned int word4;   /* +0x10 */
    unsigned int one;     /* +0x14 */
    unsigned int word6;   /* +0x18 */
};

void init_record7(struct record7 *record)
{
    record->word0 = 0;
    record->word1 = 0;
    record->word2 = 0;
    record->word3 = 0;
    record->word4 = 0;
    record->one = 1;
    record->word6 = 0;
}
