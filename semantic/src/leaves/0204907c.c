/*
 * arm9:0204907c  (20 bytes; arm9:02091aac has identical bytes)
 *
 * Original:
 *   mov  r1, #0
 *   str  r1, [r0]
 *   str  r1, [r0, #4]
 *   str  r1, [r0, #8]
 *   bx   lr
 *
 * Clears the three 32-bit words at +0x00, +0x04 and +0x08 of the record.
 * Record meaning is unknown.
 */
void pvz_0204907c_leaf(void *record)
{
    unsigned int *words = (unsigned int *)record;

    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
}
