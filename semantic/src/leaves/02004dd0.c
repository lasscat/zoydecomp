typedef struct Stream {
    int mode;              /* 0x00 */
    int r04, r08, r0c, r10, r14, r18, r1c, r20, r24, r28, r2c, r30, r34;
    int avail;             /* 0x38 */
    int r3c;               /* 0x3c */
    int cursor;            /* 0x40 */
    int total;             /* 0x44 */
} Stream;

void stream_init(Stream *s, int base, int size)
{
    int cursor = base + 4;

    s->cursor = cursor;
    s->total = size;
    size -= 0x40;
    if (size & 4)
        size -= 4;
    s->avail = size;
    s->mode = (cursor & 1) ? 0x3f : 0x1f;
    s->r04 = 0;
    s->r08 = 0;
    s->r0c = 0;
    s->r10 = 0;
    s->r14 = 0;
    s->r18 = 0;
    s->r1c = 0;
    s->r20 = 0;
    s->r24 = 0;
    s->r28 = 0;
    s->r2c = 0;
    s->r30 = 0;
    s->r34 = 0;
    s->r3c = 0;
}
