/* arm9:020c5aa0 (12 bytes)
 * ldr r0, [pc, #4]      ; r0 = 0x021db040
 * ldr r0, [r0, #0x44]   ; return the word at 0x021db084
 * bx lr
 *
 * Returns the 32-bit global word at 0x021db084.
 */
unsigned int get_global_021db084(void)
{
    return *(unsigned int *)(0x021DB040u + 0x44u);
}
