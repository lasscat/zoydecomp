/* arm9:020b1548 -- copies four words at +0x10 to first[0..3], three words at
 * +0x20 to second[0..2] and returns the 64-bit field at +0x2c.  Reconstructed
 * exactly (MWCC aligns unsigned long long members to 4 bytes here). */
typedef unsigned int u32;
typedef struct {
    u32 pad[4];
    u32 first[4];
    u32 second[3];
    unsigned long long tail;
} Source;
unsigned long long pvz_020b1548_leaf(const Source *src, u32 *first, u32 *second)
{
    first[0] = src->first[0];
    first[1] = src->first[1];
    first[2] = src->first[2];
    first[3] = src->first[3];
    second[0] = src->second[0];
    second[1] = src->second[1];
    second[2] = src->second[2];
    return src->tail;
}
