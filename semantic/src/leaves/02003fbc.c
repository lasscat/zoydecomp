/*
 * arm9:02003fbc  (40 bytes)
 *
 *   ldr   r3, [pc, #0x20]    ; literal 0x04000208
 *   mov   r1, #0
 *   ldrh  r2, [r3]           ; saved = REG[0x04000208]
 *   strh  r1, [r3]           ; REG[0x04000208] = 0
 *   ldr   r1, [r3, #0xc]     ; old = *(u32 *)(base + 0x0c)
 *   str   r0, [r3, #0xc]     ; *(u32 *)(base + 0x0c) = value
 *   ldrh  r0, [r3]           ; read back the halfword register only
 *   mov   r0, r1
 *   strh  r2, [r3]           ; REG[0x04000208] = saved
 *   bx    lr
 *
 * Swaps a 32-bit word at 0x04000214 while a 16-bit enable flag at
 * 0x04000208 is cleared and then restored, returning the previous word.
 * A third read of the flag register happens between the word store and the
 * restore; its result is unused, so the original C contains a read-back
 * statement (kept as a void cast). Base identity is unknown.
 */
unsigned int pvz_02003fbc(unsigned int value)
{
    volatile unsigned short *flag = (volatile unsigned short *)0x04000208;
    volatile unsigned int *word = (volatile unsigned int *)0x04000214;

    unsigned short saved = *flag;

    *flag = 0;
    unsigned int old = *word;
    *word = value;
    (void)*flag;
    *flag = saved;
    return old;
}
