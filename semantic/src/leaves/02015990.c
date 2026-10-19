#define SCALE (*(unsigned int *)(*(unsigned int *)0x02100c00 + 0x1318))

int sub_02015990(unsigned int *out, unsigned char *base, unsigned int value, unsigned char *p)
{
    signed char i;
    unsigned int delta;
    unsigned int *rec;

    if (value >= *(unsigned short *)(base + 0x12))
        return 0;
    i = 2;
    do {
        if (value >= *(unsigned short *)(base + i * 2 + 0xc))
            break;
        i--;
    } while (i >= 0);
    if (i < 0)
        return 0;
    delta = (value - *(unsigned short *)(base + i * 2 + 0xc)) * SCALE;
    rec = (unsigned int *)(p + 0xc + i * 16);
    out[1] = rec[2] - delta;
    if (out[1] > SCALE)
        out[1] = SCALE;
    out[2] = delta + *(unsigned int *)(base + i * 4);
    out[0] = delta + rec[0];
    *(unsigned char *)((unsigned char *)out + 0xc) = i;
    return 1;
}
