/*
 * arm9:02030260  (20 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r1, [pc, #0xc]        ; r1 = 0x02104240
 *   ldr  r2, [r1]              ; r2 = old value
 *   str  r0, [r1]              ; *0x02104240 = value
 *   mov  r0, r2                ; return old value
 *   bx   lr
 *
 * Stores a 32-bit value into the fixed word at 0x02104240 and returns the
 * previous contents. Variable meaning is unknown.
 */
unsigned int pvz_02030260_leaf(unsigned int value)
{
    unsigned int *location = (unsigned int *)0x02104240u;
    unsigned int previous = *location;

    *location = value;
    return previous;
}
