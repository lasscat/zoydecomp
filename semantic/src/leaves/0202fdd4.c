/* arm9:0202fdd4
 * Zero the two fixed global words at 0x021041a4 and 0x021041ec.
 */
void reset_two_globals(void)
{
    *(volatile unsigned int *)0x021041A4u = 0;
    *(volatile unsigned int *)0x021041ECu = 0;
}
