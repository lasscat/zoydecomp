/* arm9:020c89c0 (12 bytes)
 *
 * Returns the byte at +2 of the fixed global object at 0x021de480.
 *   ldr  r0, [pc, #4]   ; r0 = 0x021de480
 *   ldrb r0, [r0, #2]
 *   bx   lr
 */
unsigned char pvz_020c89c0_get(void)
{
    return *(unsigned char *)(0x021de480u + 2u);
}
