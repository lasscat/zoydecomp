/* arm9:0200148c
 * Pack four 8-bit descriptors into one 32-bit word stored at *out.
 * Little halves: low = (a|0x40) | b<<8, high = c | d<<8, word = low | high<<16.
 */
void pvz_0200148c_leaf(unsigned int *out, unsigned int a, unsigned int b, unsigned int c,
                       unsigned int d)
{
    unsigned int low = (a | 0x40u) | (b << 8);
    unsigned int high = c | (d << 8);

    *out = low | (high << 16);
}
