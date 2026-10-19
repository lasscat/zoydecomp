/* arm9:02028674
 * this->f00 (u32)          at +0x00
 * this->f1c (pointer)      at +0x1c
 * return ((f00 - f1c->f0c) << 13) >> 16   (16-bit window after <<13)
 */
struct Inner {
    unsigned int pad00[3]; /* +0x00..0x08 */
    unsigned int f0c;      /* +0x0c */
};

struct Outer {
    unsigned int f00;      /* +0x00 */
    unsigned int pad04[6]; /* +0x04..0x18 */
    struct Inner *f1c;     /* +0x1c */
};

unsigned int pvz_02028674_leaf(unsigned int self)
{
    struct Outer *o = (struct Outer *)self;
    unsigned int d = o->f00 - o->f1c->f0c;
    return (d << 13) >> 16;
}
