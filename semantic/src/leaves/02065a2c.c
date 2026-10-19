/* arm9:02065a2c
 * True when the word at p+0x5ae4 is 4 or 5 (i.e. (v-4) <= 1 unsigned).
 */
int is_recent_state(void *p)
{
    unsigned int v = *(unsigned int *)((char *)p + 0x5AE4);

    return (v - 4) <= 1;
}
