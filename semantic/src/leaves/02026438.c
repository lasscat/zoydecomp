/* 0x02026438: pop saved words off a frame stack back into the object's
 * 16-slot register area, guided by a 16-bit presence mask, then publish
 * the frame top. All layout offsets are documented because the real struct
 * is unknown.
 *
 * `mask` is volatile only so the compiler keeps the original's independent
 * reload of it on every iteration (the store into slots[] may alias it). */
struct Frame
{
    unsigned char pad00[0x14];    /* 0x00..0x13 unknown */
    unsigned int sp;              /* 0x14 frame top */
    unsigned int base;            /* 0x18 frame base */
    unsigned int slots[16];       /* 0x1c..0x5b restored words */
    unsigned char pad5c[4];       /* 0x5c..0x5f unknown */
    unsigned int size;            /* 0x60 frame size in bytes */
    unsigned char pad64[4];       /* 0x64..0x67 unknown */
    volatile unsigned short mask; /* 0x68 bit i => slots[i] is on the stack */
    unsigned char flag6a;         /* 0x6a nonzero => no header gap */
};

int FrameRestore(struct Frame *frame)
{
    unsigned int cur = frame->base + frame->size
                     - (frame->flag6a != 0 ? 0 : 0x10);
    int i;

    for (i = 15; i >= 0; i--)
    {
        if ((frame->mask & (1u << i)) != 0)
        {
            cur -= 4;
            frame->slots[i] = *(unsigned int *)cur;
        }
    }
    frame->sp = frame->base + frame->size;
    return (int)frame->slots[14];
}
