/* arm9:02018b94  (72 bytes = 68 code + 4 byte pool)
 *
 *   ldr  r2, [pc, #0x3c]    ; -> 0x04000204 (EXMEMCNT, pool inside extent)
 *   ldrh r1, [r2]
 *   and  r1, r1, #0xc
 *   asr  r1, r1, #2
 *   str  r1, [r0]           ; out[0] = bits 2..3
 *   ldrh r1, [r2]
 *   and  r1, r1, #0x10
 *   asr  r1, r1, #4
 *   str  r1, [r0, #4]       ; out[1] = bit 4
 *   ldrh r0, [r2]
 *   bic  r0, r0, #0xc
 *   orr  r0, r0, #0xc
 *   strh r0, [r2]           ; bits 2..3 = 3
 *   ldrh r0, [r2]
 *   bic  r0, r0, #0x10
 *   strh r0, [r2]           ; bit 4 = 0
 *   bx   lr
 *
 * Reports the two memory-bus ownership fields of the DS memory control
 * register at 0x04000204, then forces the first to 3 and clears the second.
 * The register is volatile, so every read is a fresh halfword load.
 */
void pvz_02018b94_read_and_reset(unsigned int *out)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x04000204;

    out[0] = (*reg & 0xc) >> 2;
    out[1] = (*reg & 0x10) >> 4;
    *reg = (unsigned short)((*reg & ~0xc) | 0xc);
    *reg = (unsigned short)(*reg & ~0x10);
}
