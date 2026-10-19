/* arm9:02097bf8 (40 bytes)
 * add r0, r0, #0x1ec     ; r0 = this + 0x1ec
 * add r3, r0, #0x400     ; r3 = this + 0x5ec  (byte array base)
 * and r0, r1, #7
 * mov r2, #1
 * lsl r0, r2, r0         ; r0 = 1 << (bit & 7)
 * ldrb r2, [r3, r1, lsr #3]  ; byte holding the bit
 * and r0, r0, #0xff
 * orr r0, r2, r0
 * strb r0, [r3, r1, lsr #3]
 * bx lr
 *
 * Sets bit (bit & 7) of byte number (bit >> 3) of a bit field that
 * starts 0x5ec bytes into the object. The base is formed in two steps
 * (an inner field at +0x1ec and a +0x400 sub-array); unknown layout, so
 * the offsets are kept literal.
 */
void set_bit(void *this, unsigned int bit)
{
    unsigned char *field = (unsigned char *)((char *)this + 0x1ec);
    unsigned char *bytes = field + 0x400;
    bytes[bit >> 3] |= (unsigned char)(1u << (bit & 7));
}
