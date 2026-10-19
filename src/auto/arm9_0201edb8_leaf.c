/* Length of a zero terminated 16-bit unit string, in units. */
int pvz_0201edb8_leaf(const unsigned short *s)
{
    int n = -1;
    unsigned short c;
    do {
        c = *s++;
        n++;
    } while (c != 0);
    return n;
}
