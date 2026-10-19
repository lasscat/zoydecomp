/* Same head initialisation as 0203ffa8 plus a global byte flag at 0x02105f10.
   Measured X: clang merges the two zero words into one stmib and reloads the
   flag address into r0, which shifts the whole schedule. */
struct ring_02041688 {
    unsigned int count;
    unsigned int read;
    void *data;
};

void init_ring_02041688(struct ring_02041688 *ring)
{
    ring->count = 0;
    ring->read = 0;
    ring->data = (char *)ring + 4;
    *(volatile unsigned char *)0x02105f10 = 1;
}
