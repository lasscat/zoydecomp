/* 0204de38 (arm9, 16 bytes)
 * ldr r1, [r0, #0x24]
 * add r1, r1, #1
 * str r1, [r0, #0x24]
 * bx lr
 *
 * Increment the 32-bit counter at offset 0x24 of p.
 */
void f(void *p)
{
    (*(unsigned int *)((char *)p + 0x24))++;
}
