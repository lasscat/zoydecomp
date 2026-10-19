/* arm9:0200e5b4
 * Store the argument into the fixed global word at 0x020ff660.
 */
void set_global(unsigned int value)
{
    *(volatile unsigned int *)0x020FF660u = value;
}
