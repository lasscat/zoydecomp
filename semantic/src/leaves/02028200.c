/* arm9:02028200
 * Self-relative pointer fix-up: adds the record's own address to the word
 * field at +0xc (relocating an embedded pointer once the record is placed).
 */
void relocate_self(unsigned int *self)
{
    self[3] = self[3] + (unsigned int)self;
}
