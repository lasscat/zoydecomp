/* arm9:02034194 -- returns p[5] + ((p[7] + 3) & ~3).  Reconstructed exactly. */
typedef unsigned int u32;

u32 aligned_tail(const u32 *p)
{
    return p[5] + ((p[7] + 3u) & ~3u);
}
