/* Initialises a ring head: two zero words followed by a pointer to the word
   after the head (offset 4). The volatile qualifier on the data field keeps
   clang from merging the neighbouring word stores into one stmib; the emitted
   instruction count then matches the original. */
struct ring_0203ffa8 {
    unsigned int count;
    unsigned int read;
    void *volatile data;
};

void init_ring_0203ffa8(struct ring_0203ffa8 *ring)
{
    unsigned int zero = 0;
    void *data = (char *)ring + 4;
    ring->count = zero;
    ring->read = zero;
    ring->data = data;
}
