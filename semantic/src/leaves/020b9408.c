/* Writes the two bit field taken from bits 4..5 of the word at 0xc4 into word 2
   of the block held at offset 0xb8. The original loads the full word and
   extracts with lsl #26 / lsr #30; the bitfield below is narrowed to a byte
   load by the backend. */
struct pair_020b9408 {
    unsigned int low : 4;
    unsigned int mode : 2;
};

void set_mode_020b9408(unsigned char *object)
{
    struct pair_020b9408 *flags = (struct pair_020b9408 *)(object + 0xc4);
    unsigned int *block = *(unsigned int **)(object + 0xb8);
    block[2] = flags->mode;
}
