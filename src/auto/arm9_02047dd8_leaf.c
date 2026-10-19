/*
 * arm9:02047dd8  (32 bytes)
 *
 * Original instructions:
 *   ldr   r3, [r1, #4]      ; r3 = clear mask at ops+0x04
 *   ldr   r2, [r0]          ; r2 = target word
 *   ldr   r1, [r1]          ; r1 = set mask at ops+0x00
 *   mvn   r3, r3            ; ~clear mask
 *   orr   r1, r2, r1        ; (target | set mask)
 *   and   r1, r3, r1        ; & ~clear mask
 *   str   r1, [r0]          ; store back
 *   bx    lr
 *
 * Reads a (set, clear) mask pair from *ops, then updates *target as
 *   target = (target | ops->set) & ~ops->clear
 * i.e. sets the bits in ops->set and clears the bits in ops->clear.
 * Record identities and mask value effect are unknown.
 */

struct UnknownWord {
    unsigned int field_0x00;
};

struct UnknownBitOps {
    unsigned int set_mask;
    unsigned int clear_mask;
};

void pvz_02047dd8_leaf(struct UnknownWord *target, const struct UnknownBitOps *ops)
{
    target->field_0x00 = (target->field_0x00 | ops->set_mask) & ~ops->clear_mask;
}
