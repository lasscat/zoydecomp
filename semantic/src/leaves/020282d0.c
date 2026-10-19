/* arm9:020282d0 (32 bytes)
 * ldr r0, [pc, #0x18]   ; r0 = 0x4210ffff     (pool word)
 * ldr r2, [pc, #0x18]   ; r2 = 0x040004c0
 * lsr r1, r0, #0x10     ; r1 = 0x4210
 * str r0, [r2]          ; *(u32*)0x040004c0 = 0x4210ffff
 * ldr r0, [pc, #0x10]   ; r0 = 0x001f00c0
 * str r1, [r2, #4]      ; *(u32*)0x040004c4 = 0x4210
 * str r0, [r2, #-0x1c]  ; *(u32*)0x040004a4 = 0x001f00c0
 * bx lr
 *
 * Writes three fixed display/palette control values: the same word is
 * also stored split into its upper half at the following word.
 */
void store_display_values(void)
{
    volatile unsigned int *base = (volatile unsigned int *)0x040004C0u;
    unsigned int value = 0x4210FFFFu;
    base[0] = value;
    base[1] = value >> 16;
    *(volatile unsigned int *)0x040004A4u = 0x001F00C0u;
}
