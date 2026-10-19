/* Sets the byte at offset 0x40 to 1 when it is zero; always returns 0. */
int pvz_020407b8_leaf(unsigned char *p)
{
    if (p[0x40] == 0)
        p[0x40] = 1;
    return 0;
}
