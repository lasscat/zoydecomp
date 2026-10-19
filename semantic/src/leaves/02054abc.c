/* arm9:02054abc
 * this->f6c (u32 at +0x6c) is a small state value. (f6c + 3) wraps to 0 or 1
 * only for f6c in {0xFFFFFFFD, 0xFFFFFFFE}; otherwise the result is 1.
 */
struct State {
    unsigned int pad00[27];  /* +0x00..0x68 */
    unsigned int f6c;        /* +0x6c */
};

unsigned int small(unsigned int self)
{
    struct State *s = (struct State *)self;
    return (s->f6c + 3u) > 1u;
}
