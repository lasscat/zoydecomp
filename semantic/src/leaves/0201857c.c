/* arm9:0201857c
 * Return bit 0 of the word at p+4 as a 0/1 integer.
 */
int get_bit0(void *p)
{
    return (*(unsigned int *)((char *)p + 4) & 1u) != 0;
}
