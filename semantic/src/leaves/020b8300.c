/* arm9:020b8300
 * Getter for the 32-bit field at self+0x10.
 */
unsigned int get_field_10(const void *self)
{
    return *(const unsigned int *)((const char *)self + 0x10);
}
