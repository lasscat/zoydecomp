unsigned short f(int x)
{
    unsigned char *tbl = (unsigned char *)0x020D3CD0;
    unsigned char b;
    int v;

    if (x < -723)
        x = -723;
    else if (x > 0)
        x = 0;

    b = tbl[x + 0x2D3];
    if (x < -240)
        v = 3;
    else if (x < -120)
        v = 2;
    else if (x < -60)
        v = 1;
    else
        v = 0;
    return (unsigned short)(b | (v << 8));
}
