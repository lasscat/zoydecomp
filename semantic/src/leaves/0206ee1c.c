/* Indexed lookup into a table of 0x20c-byte records; the index is truncated to
   16 bits (the original masks it explicitly). */
void *record_at(char *p, unsigned index)
{
    unsigned table = *(unsigned *)(*(unsigned *)(p + 0x67c) + 4);
    unsigned base = *(unsigned *)table;
    return (void *)(base + (unsigned short)index * 0x20c);
}
