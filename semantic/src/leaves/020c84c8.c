/* arm9:020c84c8 (24 bytes)
 * ldr r0, [pc, #0x10]   ; r0 = 0x021de480
 * ldr r0, [r0, #0x20]   ; r0 = word at 0x021de4a0
 * cmp r0, #0
 * movne r0, #1
 * moveq r0, #0
 * bx lr
 *
 * Returns 1 when the 32-bit global word at 0x021de4a0 is non-zero.
 */
int has_global_021de4a0(void)
{
    return *(unsigned int *)(0x021DE480u + 0x20u) != 0;
}
