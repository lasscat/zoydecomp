/* Initialises a four word descriptor; the last word is the constant 0xff.
   The three argument words are emitted as one stm and the constant store as a
   separate str. The volatile qualifier on the last word stops the backend from
   folding that store into the stm (store order / independence is preserved);
   the source stores it first, matching the emitted order. */
struct desc_02038f64 {
    unsigned int field0;
    unsigned int field4;
    unsigned int field8;
    volatile unsigned int fieldc;
};

void init_02038f64(struct desc_02038f64 *desc, unsigned int a, unsigned int b, unsigned int c)
{
    desc->fieldc = 0xff;
    desc->field0 = a;
    desc->field4 = b;
    desc->field8 = c;
}
