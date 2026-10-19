/* arm9:0205a1f4
 * Sets the byte flag at self+0x19c to 1.
 */
void set_byte_flag(unsigned char *self)
{
    self[0x19c] = 1;
}
