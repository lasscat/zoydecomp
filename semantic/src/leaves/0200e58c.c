/* Reads the 32-bit word of the fixed global at 0x020ff660.
 * Identity unknown; the constant pool word sits just past the extent. */
unsigned int pvz_0200e58c_get_global_word(void)
{
    return *(volatile unsigned int *)0x020ff660;
}
