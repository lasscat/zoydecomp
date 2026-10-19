/*
 * arm9:0202edb4  (28 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r1, [pc, #0x14]       ; r1 = 0x021037f0
 *   mov  r2, #1
 *   mvn  r0, r2, lsl r0        ; r0 = ~(1 << bit)
 *   ldr  r2, [r1, #4]          ; r2 = flags
 *   and  r0, r2, r0            ; r0 = flags & ~(1 << bit)
 *   str  r0, [r1, #4]          ; flags = r0
 *   bx   lr
 *
 * Clears one bit of the 32-bit flag word at 0x021037f4. Bit position beyond 31
 * wraps as the original ARM shift does. Field meaning is unknown.
 */
void pvz_0202edb4_leaf(unsigned int bit)
{
    unsigned int *flags = (unsigned int *)0x021037f0u;

    flags[1] &= ~(1u << bit);
}
