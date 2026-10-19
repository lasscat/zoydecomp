/*
 * arm9:020015b4  (36 bytes)
 *
 * Original instructions:
 *   ldr   ip, [sp]           ; 5th argument (forced bit flag)
 *   orr   r0, r0, r1, lsl #16
 *   orr   r1, r0, r3, lsl #24
 *   cmp   ip, #0
 *   ldr   r0, [pc, #0xc]     ; literal 0x04000350 (register block)
 *   orrne r1, r1, #0x8000
 *   str   r1, [r0]           ; [0x04000350] = packed control word
 *   strh  r2, [r0, #4]       ; [0x04000354] = arg2, 16-bit
 *   bx    lr
 *
 * Packs three 8-bit values into one 32-bit control word (a | b << 16 |
 * d << 24), forces bit 15 when the fifth argument is non-zero, then writes
 * that word plus a 16-bit value into a fixed hardware register pair. The
 * device behind 0x04000350/0x04000354 is unknown (register block base
 * 0x04000000). The original loads the register base from a literal pool;
 * clang materialises it with movw/movt instead.
 */
void pvz_020015b4(unsigned int a, unsigned int b, unsigned short c,
                  unsigned int d, int force_high)
{
    unsigned int control = (a | (b << 16)) | (d << 24);

    if (force_high != 0)
        control |= 0x8000;

    *(volatile unsigned int *)0x04000350 = control;
    *(volatile unsigned short *)0x04000354 = c;
}
