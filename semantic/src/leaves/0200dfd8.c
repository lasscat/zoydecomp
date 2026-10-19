/* arm9:0200dfd8
 * Busy waits until the 32-bit word at 0x020FF63C is no longer 1.
 */
void wait_not_busy(void)
{
    volatile unsigned int *flag = (volatile unsigned int *)0x020FF63C;

    while (*flag == 1)
        ;
}
