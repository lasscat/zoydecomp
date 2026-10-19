/* arm9:02003b08 (12 bytes)
 * ldr r0, [pc, #4]   ; r0 = 0x020fd340
 * ldrh r0, [r0]      ; return the 16-bit word stored there
 * bx lr
 *
 * Reads a 16-bit hardware/global word through a fixed absolute address.
 * The original keeps the address in a trailing literal pool.
 */
unsigned int read_word_020fd340(void)
{
    return *(volatile unsigned short *)0x020FD340u;
}
