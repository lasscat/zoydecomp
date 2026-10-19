/*
 * arm9:020ca934  (16 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r0, [pc, #8]          ; r0 = 0x021de53c
 *   mov  r1, #0
 *   strb r1, [r0, #4]          ; *(unsigned char *)(0x021de540) = 0
 *   bx   lr
 *
 * Clears the byte at +0x04 of the fixed block at 0x021de53c. Block meaning is
 * unknown.
 */
void pvz_020ca934_leaf(void)
{
    *(volatile unsigned char *)0x021de540u = 0;
}
