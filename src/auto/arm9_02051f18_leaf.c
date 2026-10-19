/* arm9:02051f18 (20 bytes)
 * Identical body to arm9:0204a85c (same target hash): clears the three
 * 32-bit words at offsets 0, 4 and 8.
 */
void pvz_02051f18_leaf(unsigned int *this)
{
    this[0] = 0;
    this[1] = 0;
    this[2] = 0;
}
