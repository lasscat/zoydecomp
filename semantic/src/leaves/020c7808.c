void sub_020c7808(void)
{
    unsigned int flags = *(volatile unsigned int *)0x021de250;
    unsigned char *bytes = (unsigned char *)0x021de300;
    unsigned char *a = (unsigned char *)0x021de340;
    unsigned char *b = (unsigned char *)0x021de280;
    unsigned int i;
    unsigned short v;
    unsigned short *rec;
    unsigned char lo;
    unsigned char hi;

    if (!(flags & 1))
        return;
    if (!(flags & 0x10) && (flags & 4)) {
        i = 0;
        do {
            if (bytes[0xd0 + i] == 0)
                break;
            v = *(unsigned short *)(a + i * 0x30 + 8);
            lo = (unsigned char)v;
            hi = (unsigned char)(v >> 8);
            rec = (unsigned short *)(b + i * 0xc);
            rec[4] = rec[2];
            rec[5] = rec[3];
            rec[2] = lo;
            rec[3] = hi;
            *(unsigned int *)(b + i * 0xc) = *(unsigned short *)(a + i * 0x30 + 0xa);
            i++;
        } while (i < 2);
    }
    *(volatile unsigned int *)0x021de250 |= 0x10;
}
