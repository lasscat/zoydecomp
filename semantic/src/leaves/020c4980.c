/*
 * arm9:020c4980  (24 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r1, [pc, #0x10]       ; r1 = 0x021db040
 *   ldr  r2, [r1, #0x1c]       ; r2 = state->field_0x1c
 *   sub  r2, r2, #9
 *   cmp  r2, #1
 *   strhi r0, [r1, #0x44]      ; if (unsigned)(field - 9) > 1: field_0x44 = value
 *   bx   lr
 *
 * Stores `value` at +0x44 unless the state word at +0x1c is 9 or 10.
 * Field meanings are unknown.
 */
void pvz_020c4980_leaf(unsigned int value)
{
    volatile unsigned int *state = (volatile unsigned int *)0x021db040u;

    if (state[0x1c / 4] - 9u > 1u) {
        state[0x44 / 4] = value;
    }
}
