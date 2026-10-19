/* arm9:02067c14 (40 bytes)
 * ldr r2, [r1, #0x114]  ; r2 = other->f114 (32-bit word)
 * ldr r3, [r0, #0xc]    ; r3 = this->f0c  (saved)
 * lsl r2, r2, #0x10
 * lsr r2, r2, #0x10     ; r2 = low 16 bits of other->f114
 * str r2, [r0, #0xc]    ; this->f0c = that 16-bit value
 * str r3, [r1, #0x114]  ; other->f114 = saved this->f0c
 * ldr r1, [r0, #0x10]
 * sub r1, r1, #1
 * str r1, [r0, #0x10]   ; this->f10 -= 1
 * bx lr
 *
 * Exchanges the low 16 bits of other->f114 with this->f0c and then
 * decrements the counter at this->f10. The order matters: the old
 * this->f0c is read before either store, and the counter is only touched
 * afterwards.
 */
void exchange_and_advance(void *this, void *other)
{
    unsigned int other_value = *(unsigned int *)((char *)other + 0x114);
    unsigned int saved = *(unsigned int *)((char *)this + 0x0c);
    *(unsigned int *)((char *)this + 0x0c) = other_value & 0xffffu;
    *(unsigned int *)((char *)other + 0x114) = saved;
    *(unsigned int *)((char *)this + 0x10) = *(unsigned int *)((char *)this + 0x10) - 1;
}
