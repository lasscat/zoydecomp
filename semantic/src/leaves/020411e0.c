/* arm9:020411e0
 * Clear the word at p+0x14.
 */
void clear_f14(void *p)
{
    *(unsigned int *)((char *)p + 0x14) = 0;
}
