/* Table entry update.
 * 0x020FF220 is the base of a global table of 12-byte entries:
 *   +0 int word0, +4 int word1, +8 unsigned char usage counter.
 * Fills words 0/1 of the selected entry and returns the incremented counter. */
unsigned char sub_02008420(unsigned int index, int value1, int value2)
{
    unsigned char *entry = (unsigned char *)0x020FF220u + index * 12u;

    *(int *)(entry + 0) = value1;
    *(int *)(entry + 4) = value2;
    return ++*(unsigned char *)(entry + 8);
}
