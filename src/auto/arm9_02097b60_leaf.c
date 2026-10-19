/* arm9:02097b60
 * Set bit (index & 7) of byte (index >> 3) in the bitmap that starts 0x5d8
 * bytes into p.
 */
void pvz_02097b60_leaf(unsigned char *p, unsigned int index)
{
    unsigned char *bits = (unsigned char *)p + 0x5d8;

    bits[index >> 3] |= (unsigned char)(1u << (index & 7));
}
