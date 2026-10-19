/* arm9:020bd3b4 (40 bytes)
 * push {r3, lr}
 * ldr lr, [pc, #0x1c]   ; lr = 0x0400000c
 * ldrh ip, [lr]
 * and ip, ip, #0x43
 * orr r0, ip, r0, lsl #14
 * orr r0, r0, r1, lsl #7
 * orr r0, r0, r2, lsl #8
 * orr r0, r0, r3, lsl #2
 * strh r0, [lr]         ; write the merged word back
 * pop {r3, pc}
 *
 * Read-modify-write of the 16-bit hardware register at 0x0400000c:
 * bits 0,1 and 6 are preserved, then four fields are inserted.
 */
void merge_register(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x0400000Cu;
    *reg = (unsigned short)((*reg & 0x43u) | (a << 14) | (b << 7) | (c << 8) | (d << 2));
}
