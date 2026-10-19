/* arm9:02046d34 h3 (24 bytes)
 * Volatile word stores keep the original order (count, +0x08, +0x04) and
 * the +0x08 store is addressed from the self pointer, as in the original.
 */
void init_link(void *this)
{
    volatile unsigned int *head = (volatile unsigned int *)this;
    volatile unsigned int *self = (volatile unsigned int *)((char *)this + 4);
    head[0] = 0;
    self[1] = (unsigned int)self;      /* +0x08 */
    head[1] = (unsigned int)self;      /* +0x04 */
}
