/* arm9:02051940
 * If bit 0 of the word at p is set return the pointer stored at p+8, otherwise
 * return p advanced by one byte.
 */
void *entry_pointer(void *p)
{
    if (*(unsigned int *)p & 1u)
        return *(void **)((char *)p + 8);
    return (char *)p + 1;
}
