/*
 * arm9:0201a9b0  (40 bytes)
 *
 *   ldr  r2, [r0, #0x18]
 *   ldr  r1, [r0, #0x2c]
 *   ldr  ip, [r0, #0x1c]
 *   ldr  r3, [r0, #0x20]
 *   and  r1, r2, r1
 *   sub  r1, r3, r1
 *   str  ip, [r0, #0x24]
 *   str  r1, [r0, #0x28]
 *   str  r2, [r0, #0x34]
 *   bx   lr
 *
 * Copies field 0x1c to 0x24, stores 0x20 - (0x18 & 0x2c) into 0x28 and
 * caches 0x18 into 0x34. The three stores keep the original ascending
 * order (0x24, 0x28, 0x34). Field roles are unknown.
 */
struct UnknownState_0201a9b0 {
    unsigned char pad_0x00[0x18];
    unsigned int field_0x18;
    unsigned int field_0x1c;
    unsigned int field_0x20;
    unsigned int field_0x24;
    unsigned int field_0x28;
    unsigned int field_0x2c;
    unsigned char pad_0x30[0x04];
    unsigned int field_0x34;
};

void pvz_0201a9b0(struct UnknownState_0201a9b0 *state)
{
    unsigned int value = state->field_0x18;

    state->field_0x24 = state->field_0x1c;
    state->field_0x28 = state->field_0x20 - (value & state->field_0x2c);
    state->field_0x34 = value;
}
