/*
 * arm9:020b9388  (40 bytes)  -- tier X (36-byte candidate)
 *
 * Original instructions:
 *   ldr  r2, [r0, #0xb8]     ; sub = state->sub_0xb8
 *   ldr  r1, [r2, #0x88]
 *   orr  r1, r1, #1
 *   str  r1, [r2, #0x88]     ; sub->field_0x88 |= 1
 *   ldr  r1, [r0, #0xc4]     ; flags (full 32-bit load)
 *   ldr  r0, [r0, #0xb8]     ; sub reloaded from the state
 *   lsl  r1, r1, #0x1e
 *   lsr  r1, r1, #0x1e       ; flags & 3
 *   strh r1, [r0, #0x8c]     ; sub->half_0x8c = flags & 3
 *   bx   lr
 *
 * Sets bit 0 of the sub-object's control word and forwards the low two bits of
 * the state's flag word into a 16-bit field of the same sub-object. The sub
 * pointer is read from the state twice, with no reuse.
 *
 * The volatile qualifiers reproduce the original's independent accesses: the
 * second sub-pointer load (no CSE) and the full-width flag load (clang narrows
 * a plain load to ldrh because only two bits are used). The one remaining
 * difference is size: clang emits and #3 where the original's compiler emits
 * the two-instruction lsl/lsr #30 pair, so the candidate is four bytes short.
 */
struct Sub_020b9388 {
    unsigned char pad_0x00[0x88];
    unsigned int field_0x88;
    unsigned short half_0x8c;
};

struct State_020b9388 {
    unsigned char pad_0x00[0xb8];
    struct Sub_020b9388 *volatile sub_0xb8;
    unsigned char pad_0xbc[0x08];
    volatile unsigned int flags_0xc4;
};

void pvz_020b9388(struct State_020b9388 *state)
{
    state->sub_0xb8->field_0x88 |= 1;
    state->sub_0xb8->half_0x8c = (unsigned short)(state->flags_0xc4 & 3);
}
