/* arm9:0200444c (20 bytes)
 * ldr r1, [pc, #0xc]    ; r1 = 0x020fd3c4
 * ldr r0, [r1, #0x18]
 * add r0, r0, #1
 * str r0, [r1, #0x18]   ; *(u32*)(0x020fd3c4 + 0x18) += 1
 * bx lr
 *
 * Increments a 32-bit frame counter kept in a fixed global struct whose
 * base address is 0x020fd3c4.
 */
void tick_frame_counter(void)
{
    *(volatile unsigned int *)0x020FD3DCu += 1u;
}
