/* global -> object -> word field 0x84. */
unsigned read_nested_84(void)
{
    unsigned *obj = *(unsigned **)0x02104240u;
    return *(unsigned *)((char *)obj + 0x84);
}
