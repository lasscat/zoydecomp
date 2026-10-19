/* Hit test of (a,b) against a rectangle described by an object and report the
 * matched object plus a hit kind of 4.  Layout (unknown):
 *   +0x08 x, +0x0c y, +0x10 height, +0x14 vertical extent,
 *   +0x30 width term, +0x34 vertical offset, +0x3c signed state
 * out[0] receives the object pointer, out[1] the hit kind, or two zero words.
 */
int sub_020a7ee8(unsigned char *p, int a, int b, unsigned int *out)
{
    if (*(int *)(p + 0x3c) > 0 || *(int *)(p + 0x34) == -1) {
        out[0] = 0;
        out[1] = 0;
        return 0;
    }

    int w = *(int *)(p + 0x30);
    int x = *(int *)(p + 0x08);
    int h = *(int *)(p + 0x10);
    int y = *(int *)(p + 0x0c);
    int h2 = *(int *)(p + 0x14);

    if (a >= x + w && a < x + w + h && b >= y && b < y + h2) {
        out[0] = (unsigned int)p;
        out[1] = 4;
        return 1;
    }

    out[0] = 0;
    out[1] = 0;
    return 0;
}
