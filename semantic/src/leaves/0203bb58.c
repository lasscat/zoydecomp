/* Initialise an object to its default state.
 * Layout (unknown): 0x00 vtable/handler 0x020e17d4, 0x04 byte mode, 0x08..0x14
 * four word counters set to 1, 0x18 word limit 0x2a2, 0x1c word zero,
 * 0x28 word -1, 0x2c halfword 0x7fff, 0x2e byte 0x1f.
 */
void sub_0203bb58(unsigned char *p)
{
    *(unsigned int *)(p + 0x00) = 0x020e17d4u;
    *(unsigned int *)(p + 0x08) = 1;
    *(unsigned int *)(p + 0x0c) = 1;
    *(unsigned int *)(p + 0x10) = 1;
    *(unsigned int *)(p + 0x14) = 1;
    *(unsigned int *)(p + 0x18) = 0x000002a2u;
    *(unsigned int *)(p + 0x1c) = 0;
    *(unsigned char *)(p + 0x04) = 0;
    *(unsigned int *)(p + 0x28) = 0xffffffffu;
    *(unsigned short *)(p + 0x2c) = 0x7fff;
    *(unsigned char *)(p + 0x2e) = 0x1f;
}
