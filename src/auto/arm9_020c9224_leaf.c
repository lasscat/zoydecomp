/* Stores the address base+0x00 + 4*count of the pair record into the caller's
 * word (an end-of-array pointer for a 4-byte element array). */
struct UnknownPair {
    unsigned int base_0x00;
    unsigned int count_0x04;
};

void pvz_020c9224_leaf(unsigned int *pointer_out, struct UnknownPair *pair)
{
    *pointer_out = pair->base_0x00 + pair->count_0x04 * 4;
}
