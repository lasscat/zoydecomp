/* Initialises a small state block at p (unknown object type).
 * +0x00 pointer 0x020E17D4, +0x04 cleared byte area, +8..+0x14 ones,
 * +0x18 constant 0x2A2, +0x1C zero, +0x28 -1, +0x2C halfword 0x7FFF,
 * +0x2E byte 0x1F. Field names unknown; written by offset. */
void sub_0203bbb0(unsigned char *p)
{
    *(unsigned int *)(p + 0x00) = 0x020E17D4u;
    *(unsigned int *)(p + 0x08) = 1;
    *(unsigned int *)(p + 0x0c) = 1;
    *(unsigned int *)(p + 0x10) = 1;
    *(unsigned int *)(p + 0x14) = 1;
    *(unsigned int *)(p + 0x18) = 0x000002A2u;
    *(unsigned int *)(p + 0x1c) = 0;
    *(unsigned int *)(p + 0x04) = 0;
    *(unsigned int *)(p + 0x28) = 0xffffffffu;
    *(unsigned short *)(p + 0x2c) = 0x7fff;
    *(unsigned char *)(p + 0x2e) = 0x1f;
}
