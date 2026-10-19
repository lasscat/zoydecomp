/*
 * arm9:02005670  (20 bytes, no literal pool)
 *
 * Original:
 *   lsl  r0, r0, #2            ; r0 = index * 4
 *   add  r0, r0, #0x2f00000
 *   add  r0, r0, #0xff000      ; r0 = 0x02ff0000 + index * 4
 *   ldr  r0, [r0, #0xdc4]      ; r0 = *(unsigned int *)(0x02ff0dc4 + index * 4)
 *   bx   lr
 *
 * Reads a 32-bit word from a fixed table of 4-byte entries at 0x02ff0000 whose
 * first used entry is at +0x0dc4 (entry index 0x371). 0x02ff0000 is a mirror of
 * main RAM 0x023f0000; the table's meaning is unknown.
 */
unsigned int pvz_02005670_leaf(unsigned int index)
{
    return *(volatile unsigned int *)(0x02ff0dc4u + index * 4u);
}
