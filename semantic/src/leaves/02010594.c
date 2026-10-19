/*
 * arm9:02010594  (28 bytes)
 *
 *   ldr   r2, [pc, #0x14]    ; literal 0x02ffff96 (register)
 *   ldrh  r1, [r2]
 *   tst   r1, #1
 *   ldrne r0, [pc, #0xc]     ; literal 0x0000fffe (mask)
 *   andne r0, r1, r0
 *   strhne r0, [r2]
 *   bx    lr
 *
 * If bit 0 of the 16-bit register at 0x02ffff96 is set, clears bit 0 in
 * place (new value = old & 0xfffe) and clears nothing otherwise. The
 * original ANDs with a mask loaded from the pool; clang prefers a single
 * BIC with the immediate #1.
 */
void pvz_02010594(void)
{
    volatile unsigned short *status = (volatile unsigned short *)0x02ffff96;
    unsigned short value = *status;

    if ((value & 1) != 0)
        *status = value & 0xfffe;
}
