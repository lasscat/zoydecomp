/* arm9:0201d378
 * 15-bit linear congruential generator.  Advances the 32-bit seed at
 * 0x020E091C with the standard multiplier/addend pair (0x41C64E6D, 0x3039)
 * and returns bits 16..30 of the new seed (0..0x7FFF).
 * The original keeps the three constants (0x020E091C, 0x41C64E6D, 0x7FFF) in
 * a literal pool placed after bx lr.
 */
unsigned int next_random(void)
{
    unsigned int *seed = (unsigned int *)0x020E091Cu;
    unsigned int value = *seed * 0x41C64E6Du + 0x3039u;

    *seed = value;

    return (value >> 16) & 0x7FFFu;
}
