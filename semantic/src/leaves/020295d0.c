/* arm9:020295d0 (32 bytes)
 * ldr r3, [r0]          ; r3 = this->f00
 * cmp r3, #1
 * ldrheq r3, [r0, #0x12] ; if f00 == 1: r3 = this->f12
 * strheq r1, [r0, #0xc]  ;               this->f0c = a
 * strheq r2, [r0, #0xe]  ;               this->f0e = b
 * orreq  r1, r3, #8      ;               this->f12 = r3 | 8
 * strheq r1, [r0, #0x12]
 * bx lr
 *
 * When the 32-bit state word at +0x00 equals 1, store the two 16-bit
 * values a and b at +0x0c/+0x0e and set bit 3 of the 16-bit flags word
 * at +0x12, preserving its other bits. The flags word is read before the
 * two stores, as in the original.
 */
void set_pair(void *this, unsigned short a, unsigned short b)
{
    if (*(unsigned int *)this == 1u) {
        unsigned short flags = *(unsigned short *)((char *)this + 0x12);
        *(unsigned short *)((char *)this + 0x0c) = a;
        *(unsigned short *)((char *)this + 0x0e) = b;
        *(unsigned short *)((char *)this + 0x12) = flags | 8;
    }
}
