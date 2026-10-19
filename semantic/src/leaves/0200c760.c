/* arm9:0200c760 (12 bytes)
 * ldr r0, [pc, #4]      ; r0 = 0x02ffff90
 * ldr r0, [r0]
 * bx lr
 *
 * Returns the 32-bit global word stored at 0x02ffff90.
 */
unsigned int get_global_02ffff90(void)
{
    return *(volatile unsigned int *)0x02FFFF90u;
}
