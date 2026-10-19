/* arm9:0200bbd8
 * Returns the word held by the global pointer/counter at 0x020FF59C.
 * The address comes from a literal pool in the original.
 */
unsigned int get_global_counter(void)
{
    return *(volatile unsigned int *)0x020FF59Cu;
}
