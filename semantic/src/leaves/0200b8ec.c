/* 0200b8ec (arm9, 16 bytes)
 * ldr r0, [r0, #0x20]   ; r0 = p->field_0x20 (a pointer)
 * ldr r0, [r0]          ; r0 = *that  (first word of pointed-to object)
 * add r0, r0, r1        ; r0 += i
 * bx lr
 *
 * Returns the first word of the object referenced by the pointer stored at
 * offset 0x20 in p, plus i.
 */
unsigned int f(void *p, unsigned int i)
{
    unsigned int *obj = *(unsigned int **)((char *)p + 0x20);
    return *obj + i;
}
