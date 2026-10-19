/* arm9:020306c0 (28 bytes)
 * ldr r1, [pc, #0x14]   ; r1 = 0x02104240
 * ldr r1, [r1]          ; r1 = pointer held there
 * ldr r2, [r1, #0x7c]
 * ldr r1, [r1, #0x80]
 * str r2, [r0]          ; dst[0] = object->f7c
 * str r1, [r0, #4]      ; dst[1] = object->f80
 * bx lr
 *
 * Copies the two 32-bit words at +0x7c and +0x80 of the object found
 * through the global pointer at 0x02104240 into the destination pair.
 */
void copy_pair(void *dst)
{
    unsigned int *object = *(unsigned int **)0x02104240u;
    unsigned int a = *(unsigned int *)((char *)object + 0x7c);
    unsigned int b = *(unsigned int *)((char *)object + 0x80);
    *(unsigned int *)dst = a;
    *(unsigned int *)((char *)dst + 4) = b;
}
