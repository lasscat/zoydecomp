/* Low 5 bits of the byte at [p+8], or 0 when that pointer is null. */
int func_02024a60(char *p) {
    unsigned char *q = *(unsigned char **)(p + 8);
    if (q == 0)
        return 0;
    return (unsigned char)(*q & 0x1F);
}
