/* arm9:020c64d8
 * Return the fixed global word at 0x021dde20.
 */
unsigned int get_global_021dde20(void)
{
    return *(unsigned int *)0x021DDE20u;
}
