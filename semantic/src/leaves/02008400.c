/* Table of 12-byte records at 0x020ff220; increments the byte counter at
   offset 8 of the record selected by the argument (used as a use counter). */
struct record_020ff220 {
    unsigned int field0;
    unsigned int field4;
    unsigned char count;
    unsigned char pad[3];
};

void bump_02008400(unsigned int index)
{
    struct record_020ff220 *table = (struct record_020ff220 *)0x020ff220;
    table[index].count++;
}
