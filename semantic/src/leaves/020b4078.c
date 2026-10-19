void sub_020b4078(int unused, unsigned int *out, unsigned int **src, int which)
{
    unsigned int *q = (unsigned int *)0x020e99ec;
    unsigned int *g = (unsigned int *)0x02108d70;

    if (which == 0 || which == 3) {
        if (src != 0) {
            ((unsigned char *)*src)[0x14] = q[1];
            ((unsigned char *)*src)[1] = q[4];
        }
        out[3] = g[1];
        return;
    }
    if (which == 1 || which == 4) {
        if (src != 0) {
            ((unsigned char *)*src)[0x14] = q[0];
            ((unsigned char *)*src)[1] = q[3];
        }
        out[3] = g[1];
        return;
    }
    if (which == 2 || which == 5) {
        if (src != 0) {
            ((unsigned char *)*src)[0x14] = q[5];
            ((unsigned char *)*src)[1] = q[2];
        }
        out[3] = g[1];
        return;
    }
}
