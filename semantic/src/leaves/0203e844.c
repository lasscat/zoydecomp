/* arm9:0203e844 h2 (36 bytes)
 * The two adjacent byte flags are declared volatile so the compiler keeps
 * them as two independent byte stores; without it clang merges them into
 * one 16-bit store, which the original does not do.
 */
struct Node {
    unsigned int f00;                 /* +0x00 */
    unsigned int f04;                 /* +0x04 */
    unsigned int f08;                 /* +0x08 */
    unsigned int f0c;                 /* +0x0c */
    unsigned int f10;                 /* +0x10 */
    unsigned int f14;                 /* +0x14 */
    unsigned int f18;                 /* +0x18 */
    unsigned int f1c;                 /* +0x1c */
    volatile unsigned char f20;       /* +0x20 */
    volatile unsigned char f21;       /* +0x21 */
};

void init_node(struct Node *this, unsigned int owner)
{
    this->f1c = owner;
    this->f0c = 0x0c;
    this->f04 = 1;
    this->f20 = 0;
    this->f21 = 0;
}
