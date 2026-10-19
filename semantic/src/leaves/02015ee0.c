/* arm9:02015ee0
 * Clears the five byte counters at +0x25..+0x29 of the global record at
 * 0x02100B50 (stored in ascending order, one byte at a time).
 */
void reset_byte_counters(void)
{
    volatile unsigned char *record = (volatile unsigned char *)0x02100B50u;

    record[0x25] = 0;
    record[0x26] = 0;
    record[0x27] = 0;
    record[0x28] = 0;
    record[0x29] = 0;
}
