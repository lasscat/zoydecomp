/* arm9:02030708 (24 bytes)
 *
 * Writes a word into a 16-byte-stride table reached through a fixed global
 * pointer chain.
 *   r2 = *(int *)0x02104240        ; global object pointer
 *   r2 = *(int *)(r2 + 0x90)       ; table base pointer
 *   r0 = r2 + index * 16
 *   *(int *)(r0 + 0x14) = value
 *   bx  lr
 *
 * Unknown offset note: +0x90 of the global object holds the table pointer;
 * +0x14 is the written field inside each 16-byte element.
 */
void pvz_02030708_set(unsigned int index, int value)
{
    char *object = *(char **)0x02104240u;
    char *table = *(char **)(object + 0x90);
    *(int *)(table + index * 16u + 0x14) = value;
}
