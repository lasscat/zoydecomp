/* Predicate: true when the flag byte at 0xdc is set or the word at 0x28 is
 * in 1..3. */
int sub_0208c240(unsigned char *obj)
{
    unsigned int v;

    if (obj[0xdc] != 0)
        return 1;

    v = *(unsigned int *)(obj + 0x28) - 1;
    if (v > 2)
        return 0;
    return 1;
}
