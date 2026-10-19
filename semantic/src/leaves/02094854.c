/* 0x02094854: reset the main level object. Stores the given id, resets
 * counters/flags and refills a 0x80-entry index table at +0x90 with its
 * own indices.
 *
 * The object pointer is volatile so the compiler keeps the original's store
 * order (each store is independent and must not be reordered).
 * The 0x80-word loop zero-fills the table; it does not store the index. */
struct LevelObject
{
    unsigned int id;            /* 0x00 */
    unsigned char flag04;       /* 0x04 */
    unsigned char pad05[0x83];  /* 0x05..0x87 */
    unsigned int f88;           /* 0x88 */
    unsigned int f8c;           /* 0x8c */
    unsigned int table[0x80];   /* 0x90..0x28f index table */
    unsigned int pad290;        /* 0x290 unknown */
    unsigned int f294;          /* 0x294 */
    unsigned char f298;         /* 0x298 */
    unsigned char pad299[0x7f]; /* 0x299..0x317 */
    unsigned int f318;          /* 0x318 */
};

void LevelObjectReset(volatile struct LevelObject *obj, unsigned int id)
{
    int i;

    obj->f294 = 0x64;
    obj->id = id;
    obj->f88 = 0;
    obj->flag04 = 0;
    obj->f8c = 0;
    obj->f298 = 0;
    obj->f318 = 0;

    for (i = 0; i < 0x80; i++)
        obj->table[i] = 0;
}
