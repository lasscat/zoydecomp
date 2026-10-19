/* arm9:02005cd0 (12 bytes)
 * ldr r0, [pc, #4]      ; r0 = 0x020fd6e4
 * ldrh r0, [r0]
 * bx lr
 *
 * Identical instruction sequence to arm9:02003b08 but reading the 16-bit
 * global word at 0x020fd6e4.
 */
unsigned int read_word_020fd6e4(void)
{
    return *(volatile unsigned short *)0x020FD6E4u;
}
