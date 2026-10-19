/* arm9:0200693c
 * Clears the 32-bit counter at 0x020FD718 and then the nine halfword entries
 * starting at 0x020FD71C.
 */
void reset_entries(void)
{
    volatile unsigned int *count = (volatile unsigned int *)0x020FD718;
    volatile unsigned short *entries = (volatile unsigned short *)0x020FD71C;
    int i = 0;

    *count = 0;
    do {
        entries[i] = 0;
        i++;
    } while (i < 9);
}
