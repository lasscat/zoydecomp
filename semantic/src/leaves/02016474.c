/* Status query on an object.
 * Offset 0x40 is a halfword state (1 = active), offset 0x4b a byte flags field
 * (bit 1 checked). The original keeps two branch/return blocks: it returns 1
 * only when state == 1 and the flag bit is set, otherwise 0. Written as a
 * short-circuit condition so the two tests stay separate. */
int sub_02016474(unsigned char *obj)
{
    if (*(unsigned short *)(obj + 0x40) == 1 && (obj[0x4b] & 2) != 0)
        return 1;
    return 0;
}
