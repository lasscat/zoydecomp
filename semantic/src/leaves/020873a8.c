/* arm9:020873a8 (28 bytes)
 * ldr r1, [r0, #0xa4]   ; r1 = this->fa4
 * cmp r1, #0
 * ldrle r0, [r0, #0xa0] ; if fa4 <= 0: r0 = this->fa0
 * cmple r0, #0
 * movgt r0, #1
 * movle r0, #0
 * bx lr
 *
 * True when the signed word at +0xa4 is positive, or when it is
 * non-positive and the signed word at +0xa0 is positive.
 */
int is_active(void *this)
{
    int limit = *(int *)((char *)this + 0xa4);
    if (limit > 0)
        return 1;
    return *(int *)((char *)this + 0xa0) > 0;
}
