/*
 * Packs four "slot present" halfwords read from a descriptor into the low
 * nibble of the result. The global at 0x02100BF0 stores the descriptor
 * pointer in its field +0xC.
 *   desc[+0x12] -> bit 1 (2)
 *   desc[+0x0E] -> bit 0 (1)
 *   desc[+0x14] -> bit 2 (4)
 *   desc[+0x16] -> bit 3 (8)
 * All field offsets within the descriptor are unverified.
 */
unsigned int slot_flags(void)
{
    unsigned char *desc = *(unsigned char **)(0x02100bf0 + 0xC);
    unsigned int flags = 0;

    if (*(unsigned short *)(desc + 0x12) != 0)
        flags |= 2;
    if (*(unsigned short *)(desc + 0x0E) != 0)
        flags |= 1;
    if (*(unsigned short *)(desc + 0x14) != 0)
        flags |= 4;
    if (*(unsigned short *)(desc + 0x16) != 0)
        flags |= 8;

    return flags & 0xff;
}
