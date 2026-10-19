/* 0x02058938: true when the object selected by index has a "simple"
 * kind value. Only indices 0..2 are valid. */
struct KindHolder
{
    unsigned char pad00[0x30]; /* 0x00..0x2f unknown */
    unsigned int kind;         /* 0x30 */
};

int SlotIsSimple(int *world, int index)
{
    unsigned int kind;

    if (index < 0)
        return 0;
    if (index > 2)
        return 0;

    kind = ((struct KindHolder *)*(int *)((char *)world + 0x17c + index * 4))->kind;
    if (kind == 1 || kind == 2 || kind == 3 || kind == 0x16)
        return 1;
    if (kind == 4 || kind == 5)
        return 1;
    return 0;
}
