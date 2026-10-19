/* arm9:020b64b8
 * Programs a three-word timer block at self+0x564: the constant 10 goes to
 * +0x564, then the two values go to +0x56c and +0x570 (source order keeps
 * the constant store last, so clang hoists mov r3,#10 to the top).
 */
void set_timer_block(void *self, unsigned int value_a, unsigned int value_b)
{
    unsigned char *base = (unsigned char *)self;

    *(unsigned int *)(base + 0x56c) = value_a;
    *(unsigned int *)(base + 0x570) = value_b;
    *(unsigned int *)(base + 0x564) = 10;
}
