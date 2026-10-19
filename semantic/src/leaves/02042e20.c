/* Byte-identical twin of 0203ffa8 (same target hash): two zero words plus the
   self pointing data pointer at offset 8. */
struct ring_02042e20 {
    unsigned int count;
    unsigned int read;
    void *volatile data;
};

void init_ring_02042e20(struct ring_02042e20 *ring)
{
    unsigned int zero = 0;
    void *data = (char *)ring + 4;
    ring->count = zero;
    ring->read = zero;
    ring->data = data;
}
