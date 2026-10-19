/*
 * arm9:020cc634  (40 bytes)
 *
 *   push  {r3, lr}
 *   ldr   lr, [pc, #0x1c]    ; literal 0x0400100c (16-bit register)
 *   ldrh  ip, [lr]
 *   and   ip, ip, #0x43
 *   orr   r0, ip, r0, lsl #14
 *   orr   r0, r0, r1, lsl #7
 *   orr   r0, r0, r2, lsl #8
 *   orr   r0, r0, r3, lsl #2
 *   strh  r0, [lr]
 *   pop   {r3, pc}
 *
 * Read-modify-write of the 16-bit register at 0x0400100c: keeps bits 0, 1
 * and 6 and inserts four caller values at bit positions 14, 7, 8 and 2.
 * The original saves the frame with push {r3, lr} because it keeps the
 * register address in lr; clang uses a different scratch register and no
 * frame, and materialises the literal with movw/movt.
 */
void pvz_020cc634(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100c;
    unsigned int value = (*reg & 0x43) | (a << 14) | (b << 7) | (c << 8) | (d << 2);

    *reg = (unsigned short)value;
}
