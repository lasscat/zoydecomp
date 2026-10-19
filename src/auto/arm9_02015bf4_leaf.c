/* arm9:02015bf4 -- one's-complement 16-bit fold of count/2 halfwords:
 * sums the halfwords, folds the carry (low + high, then again) and returns
 * the complement of the 16-bit result.  Reconstructed exactly. */
typedef unsigned short u16;
typedef unsigned int u32;
u16 pvz_02015bf4_leaf(const u16 *data, int count)
{
    u32 sum = 0;
    int n = count >> 1;
    if (n > 0) {
        do {
            sum += *data++;
        } while (--n > 0);
    }
    return (u16)(((sum & 0xffffu) + (sum >> 16) + (((sum & 0xffffu) + (sum >> 16)) >> 16)) ^
                 0xffffu);
}
