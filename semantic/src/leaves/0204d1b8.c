/* arm9:0204d1b8
 * Copy four words from src to dst; the original performs four independent
 * loads followed by four independent stores.
 * volatile reproduces those separate accesses (clang would otherwise emit
 * LDM/STM or interleave load/store pairs).
 */
void copy_quad(volatile unsigned int *dst, volatile unsigned int *src)
{
    unsigned int a = src[0];
    unsigned int b = src[1];
    unsigned int c = src[2];
    unsigned int d = src[3];

    dst[0] = a;
    dst[1] = b;
    dst[2] = c;
    dst[3] = d;
}
