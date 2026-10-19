/* arm9:02042d60 h3 (24 bytes)
 * All three words are stored through a volatile pointer so the original
 * order (count, first, self-pointer) and the early self-address
 * computation survive.
 */
void init_head(void *this)
{
    volatile unsigned int *w = (volatile unsigned int *)this;
    unsigned int *self = (unsigned int *)((char *)this + 4);
    w[0] = 0;
    w[1] = 0;
    w[2] = (unsigned int)self;
}
