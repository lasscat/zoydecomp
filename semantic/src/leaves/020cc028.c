/*
 * arm9:020cc028  (40 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   push    {r3, lr}
 *   ldr     lr, [pc, #0x1c]    ; lr = 0x0400100e
 *   ldrh    ip, [lr]           ; ip = current register value
 *   and     ip, ip, #0x43      ; keep bits 0, 1 and 6
 *   orr     r0, ip, r0, lsl #14
 *   orr     r0, r0, r1, lsl #7
 *   orr     r0, r0, r2, lsl #8
 *   orr     r0, r0, r3, lsl #2
 *   strh    r0, [lr]
 *   pop     {r3, pc}
 *
 * Read-modify-write of the 16-bit register at 0x0400100e: bits 0, 1 and 6 are
 * preserved and four fields are written - the first at bit 14, the second at
 * bit 7, the third at bit 8 and the fourth at bit 2. Field meanings are
 * unknown; `volatile` states the hardware interpretation.
 */
void pvz_020cc028_leaf(unsigned int field_14, unsigned int field_7,
                       unsigned int field_8, unsigned int field_2)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x0400100eu;
    unsigned short kept = (unsigned short)(*reg & 0x43u);
    unsigned short value = (unsigned short)(kept
                                            | (field_14 << 14)
                                            | (field_7 << 7)
                                            | (field_8 << 8)
                                            | (field_2 << 2));

    *reg = value;
}
