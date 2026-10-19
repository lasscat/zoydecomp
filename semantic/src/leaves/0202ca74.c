/* arm9:0202ca74
 * Tests bit 1 of the 32-bit state word at self+0x24.
 */
int has_second_flag(const unsigned int *self)
{
    return (self[9] & 2u) != 0;
}
