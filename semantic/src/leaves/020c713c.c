/*
 * arm9:020c713c  (20 bytes)
 *
 *   ldr  r2, [pc, #0xc]      ; literal 0x04000208
 *   mov  r1, #1
 *   ldrh r0, [r2]            ; old = REG[0x04000208]
 *   strh r1, [r2]            ; REG[0x04000208] = 1
 *   bx   lr
 *
 * Reads the 16-bit enable register at 0x04000208 and immediately writes 1
 * to it, returning the previous value.
 */
unsigned short pvz_020c713c(void)
{
    volatile unsigned short *flag = (volatile unsigned short *)0x04000208;
    unsigned short old = *flag;

    *flag = 1;
    return old;
}
