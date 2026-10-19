/* arm9:020a7f74 (28 bytes)
 * ldr r1, [r0, #0x50]   ; r1 = this->f50
 * mov r0, #0
 * cmp r1, #0
 * ldrbne r1, [r1, #0x391]
 * cmpne r1, #0
 * movne r0, #1
 * bx lr
 *
 * True when the pointer at +0x50 is non-null and the byte at +0x391 of
 * the object it points to is non-zero.
 */
int is_marked(void *this)
{
    void *child = *(void **)((char *)this + 0x50);
    return child != 0 && *(unsigned char *)((char *)child + 0x391) != 0;
}
