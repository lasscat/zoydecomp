/* arm9:02095890
 * Copies the global word at 0x021069F4 into *dst.
 * The address is loaded from a literal pool in the original.
 */
void get_global_word(unsigned int *dst)
{
    *dst = *(volatile unsigned int *)0x021069F4u;
}
