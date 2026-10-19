/* arm9:020b675c (28 bytes)
 * ldr r1, [r1, #0x30]   ; r1 = other->f30
 * cmp r1, #0
 * moveq r1, #0
 * streq r1, [r0, #0x560] ; if other->f30 == 0: this->f560 = 0
 * mov r1, #0
 * str r1, [r0, #0x55c]   ; this->f55c = 0
 * bx lr
 *
 * Clears the counter at +0x55c, and also clears the word at +0x560 when
 * the word at +0x30 of the second argument is zero.
 */
void maybe_reset(void *this, void *other)
{
    if (*(unsigned int *)((char *)other + 0x30) == 0)
        *(unsigned int *)((char *)this + 0x560) = 0;
    *(unsigned int *)((char *)this + 0x55c) = 0;
}
