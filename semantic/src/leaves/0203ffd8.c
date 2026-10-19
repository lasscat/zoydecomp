/* arm9:0203ffd8 h2 (24 bytes)
 * Same operation expressed with raw words; the original computes the
 * self-address before the two stores, clang sinks it to its use.
 */
void init_head(void *this)
{
    unsigned int *self = (unsigned int *)((char *)this + 4);
    *(unsigned int *)this = 0;
    *(unsigned int *)((char *)this + 4) = 0;
    *(unsigned int *)((char *)this + 0x0c) = (unsigned int)self;
}
