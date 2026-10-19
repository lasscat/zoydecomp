unsigned int sub_02028aa0(unsigned short *a, int *b)
{
    unsigned int flag;
    unsigned int cur;
    unsigned short space;
    unsigned int ok;
    unsigned int idx;
    unsigned int base;
    unsigned short *elem;
    unsigned int n;

    cur = a[6];
    flag = 0;
    if (a[7] <= cur + 1) {
        if (a[5] <= cur)
            flag = 1;
    }
    space = flag ? (unsigned short)(cur - a[7] + 1) : 0;
    ok = space >= 1;
    if (ok == 0)
        return 0xfffe;
    idx = *(unsigned int *)a;
    base = 0x02101824 + idx * 0x540;
    elem = (unsigned short *)(base + 0x100 + a[7] * 32);
    elem[3] = (unsigned short)(b[0] >> 4);
    elem[7] = (unsigned short)(b[1] >> 4);
    elem[11] = (unsigned short)(b[2] >> 4);
    elem[15] = (unsigned short)(b[3] >> 4);
    n = a[7];
    a[7] = n + 1;
    return n;
}
