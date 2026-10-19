/* arm9:0203991c
 * Setter for the 32-bit field at self+0x38.
 */
void set_field_38(void *self, unsigned int value)
{
    *(unsigned int *)((char *)self + 0x38) = value;
}
