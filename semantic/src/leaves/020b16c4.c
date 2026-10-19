/* arm9:020b16c4 (28 bytes)
 * ldr r3, [pc, #0x14]   ; r3 = 0x020e9844 (pool word)
 * mov r2, #0
 * mov r1, #8
 * str r3, [r0]          ; dst[0] = 0x020e9844
 * str r2, [r0, #4]      ; dst[1] = 0
 * str r1, [r0, #8]      ; dst[2] = 8
 * bx lr
 *
 * Fills a three-word descriptor: a fixed address, zero and the value 8.
 */
void init_descriptor(unsigned int *dst)
{
    dst[0] = 0x020E9844u;
    dst[1] = 0;
    dst[2] = 8;
}
