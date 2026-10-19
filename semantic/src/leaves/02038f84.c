/* arm9:02038f84 h2 (36 bytes)
 * The original copies three words with three separate loads and three
 * separate stores; volatile on both sides keeps clang from merging them
 * into ldm/stm pairs.
 */
struct Vec4 {
    volatile unsigned int f00;        /* +0x00 */
    volatile unsigned int f04;        /* +0x04 */
    volatile unsigned int f08;        /* +0x08 */
    volatile unsigned int f0c;        /* +0x0c */
};

void copy3_and_fill(struct Vec4 *dst, const struct Vec4 *src)
{
    unsigned int a = src->f00;
    unsigned int b = src->f04;
    unsigned int c = src->f08;
    dst->f00 = a;
    dst->f04 = b;
    dst->f08 = c;
    dst->f0c = 0xff;
}
