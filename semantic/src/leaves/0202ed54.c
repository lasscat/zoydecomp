/* arm9:0202ed54
 * Clear the bits of the fixed global word at 0x021037f0 given by mask.
 */
void clear_global_flags(unsigned int mask)
{
    *(volatile unsigned int *)0x021037F0u &= ~mask;
}
