struct T { unsigned char p[0xc]; int ox; short oy; short h; };
int f(struct T *t, int x, int y)
{
    int dx = x - t->ox;
    int dy = y - (int)t->oy;
    if (dx < 0 || (dx == 0 && dy < 0))
        return 0;
    {
        short h = t->h;
        if (dy < 0) {
            dy = dy + 7;
            dy = dy + 0x100;
        }
        return dy <= (int)h ? 1 : 2;
    }
}
