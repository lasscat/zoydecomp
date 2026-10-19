/* arm9:0201d3ac (12 bytes)
 * ldr r1, [pc, #4]      ; r1 = 0x020e091c
 * str r0, [r1]          ; *(u32*)0x020e091c = value
 * bx lr
 *
 * Stores a 32-bit value into the fixed global word at 0x020e091c.
 */
void store_global_020e091c(unsigned int value)
{
    *(volatile unsigned int *)0x020E091Cu = value;
}
