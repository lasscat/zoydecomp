/* arm9:020cad60 (12 bytes)
 *
 * Returns the word at +0xc of the fixed global object at 0x021de53c.
 *   ldr r0, [pc, #4]   ; r0 = 0x021de53c
 *   ldr r0, [r0, #0xc]
 *   bx  lr
 */
int pvz_020cad60_get(void)
{
    return *(int *)(0x021de53cu + 0xc);
}
