/* arm9:02027ed8
 * Entry pointer for p->count: table base at p+4, stride 16 when bit 0 of the
 * halfword at p+2 is set, otherwise stride 8.
 */
unsigned char *table_entry(void *p)
{
    unsigned int count = *(unsigned short *)p;
    unsigned char *base = *(unsigned char **)((char *)p + 4);

    if (*(unsigned short *)((char *)p + 2) & 1)
        return base + count * 16;
    return base + count * 8;
}
