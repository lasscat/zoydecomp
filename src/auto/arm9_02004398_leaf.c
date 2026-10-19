/* arm9:02004398
 * Halfword getter: returns the 16-bit field at self+4.
 */
unsigned short pvz_02004398_leaf(const void *self)
{
    return *(const unsigned short *)((const char *)self + 4);
}
