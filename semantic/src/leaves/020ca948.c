/*
 * arm9:020ca948  (16 bytes)
 *
 *   ldr  r0, [pc, #8]        ; literal 0x021de53c
 *   mov  r1, #1
 *   strb r1, [r0, #2]
 *   bx   lr
 *
 * Sets the byte at 0x021de53e to 1.
 */
void pvz_020ca948(void)
{
    *(unsigned char *)((char *)0x021de53c + 2) = 1;
}
