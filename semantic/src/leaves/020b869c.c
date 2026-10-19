/* arm9:020b869c (12 bytes)
 *
 * Returns the fixed global word at 0x020f3760.
 *   ldr r0, [pc, #4]   ; r0 = 0x020f3760
 *   ldr r0, [r0]
 *   bx  lr
 */
int pvz_020b869c_get(void)
{
    return *(int *)0x020f3760u;
}
