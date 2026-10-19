/* arm9:02001664
 * Returns a 5-bit field (bits 8..12) of the 16-bit hardware register at
 * 0x0A100004, moved up to bit 11 and biased by 0x06200000 (i.e. a
 * 0x800-byte-granular background base address in the 0x06000000 VRAM area).
 * The original loads the register address from a literal pool whose word
 * lives in the inter-function gap at 0x02001680; clang keeps its pool word
 * inside .text, so the emitted block is 4 bytes longer.
 */
unsigned int get_bg_base(void)
{
    unsigned int value = *(volatile unsigned short *)0x0A100004u;

    return ((value & 0x1F00u) >> 8 << 11) + 0x06200000u;
}
