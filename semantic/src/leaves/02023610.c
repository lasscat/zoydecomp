/* arm9:02023610 -- merges bit 31 of the fourth word of a 16-byte block into
 * the second word and returns the first word.  The original copies the block
 * to the stack and writes the updated word back.  N: MWCC keeps the OR result
 * in r0 and stores before reloading w0; registers differ, bytes are 2 insns. */
typedef struct { unsigned int w0, w1, w2, w3; } Block;
unsigned int take_high_bit(volatile Block blk)
{
    blk.w1 = (blk.w1 & 0x7fffffffu) | (blk.w3 & 0x80000000u);
    return blk.w0;
}
