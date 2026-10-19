/* arm9:02043554 (12 bytes)
 * ldr r1, [r1, #8]      ; src->f08
 * str r1, [r0]          ; dst->f00 = src->f08
 * bx lr
 *
 * Copies the 32-bit word at +0x08 of the second argument to offset 0 of
 * the first.
 */
void pvz_02043554_leaf(void *dst, void *src)
{
    *(unsigned int *)dst = *(unsigned int *)((char *)src + 0x08);
}
