/* arm9:020cacf4 (12 bytes)
 * ldr r0, [pc, #4]      ; r0 = 0x021de53c
 * ldr r0, [r0, #0x10]   ; return the word at 0x021de54c
 * bx lr
 *
 * Returns the 32-bit global word at 0x021de54c.
 */
unsigned int get_global_021de54c(void)
{
    return *(unsigned int *)(0x021DE53Cu + 0x10u);
}
