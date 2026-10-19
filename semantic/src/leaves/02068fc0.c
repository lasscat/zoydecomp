/* arm9:02068fc0
 * Clamps value into the signed range 0..0x1f and stores it as the 16-bit
 * field at self+0xd0.
 */
void set_level(void *self, int value)
{
    if (value < 0)
        value = 0;
    if (value > 0x1f)
        value = 0x1f;

    *(unsigned short *)((char *)self + 0xd0) = (unsigned short)value;
}
