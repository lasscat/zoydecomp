/* arm9:020100ac
 * Return the 32-bit field at 0x020fffec + 4 (fixed global record).
 */
unsigned int get_global_field4(void)
{
    return *(unsigned int *)(0x020FFFECu + 4);
}
