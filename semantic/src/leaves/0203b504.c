/*
 * arm9:0203b504  (32 bytes)
 *
 * Original:
 *   ldr   r1, [r0]             ; r1 = header word
 *   lsl   r1, r1, #0x1f
 *   lsrs  r1, r1, #0x1f        ; extract bit 0 -> flags
 *   ldrbeq r0, [r0]            ; bit 0 clear: take the 7-bit field in byte 0
 *   lslseq r0, r0, #0x18
 *   lsreq r0, r0, #0x19        ; r0 = (byte0 << 24) >> 25  (bits 1..7)
 *   ldrne r0, [r0, #4]         ; bit 0 set: take the 32-bit word at +0x04
 *   bx    lr
 *
 * Returns either the 32-bit payload at +0x04 (when bit 0 of the header word is
 * set) or the 7-bit field held in bits 1..7 of the header word. Header layout
 * and its meaning is unknown.
 */

struct DiscriminatedValue {
    unsigned int is_payload : 1;   /* +0x00 bit 0 */
    unsigned int small_value : 7;  /* +0x00 bits 1..7 */
    unsigned int unknown : 24;     /* +0x00 bits 8..31 */
    unsigned int payload;          /* +0x04 */
};

unsigned int pvz_0203b504_leaf(const struct DiscriminatedValue *value)
{
    if (value->is_payload != 0) {
        return value->payload;
    }
    return value->small_value;
}
