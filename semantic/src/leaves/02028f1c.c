/*
 * arm9:02028f1c  (12 bytes)
 *
 *   add  r0, r0, r1, lsl #2
 *   str  r2, [r0, #8]
 *   bx   lr
 *
 * Stores a 32-bit value at base + index * 4 + 8 (a 32-bit table entry two
 * words past the array start). No bounds check is performed.
 */
void pvz_02028f1c(unsigned int *base, unsigned int index, unsigned int value)
{
    *(unsigned int *)((char *)base + index * 4 + 8) = value;
}
