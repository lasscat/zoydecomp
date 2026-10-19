/* Copies the word at state+0x18 to state+0x24 and clears state+0x2c.  The two
 * target fields are volatile so the original order (load 0x18, materialise 0,
 * store 0x24, store 0x2c) is preserved; without volatile this compiler hoists
 * the 0x2c clear in front of the load. */
struct UnknownState {
    unsigned char unknown_0x00_0x17[0x18];
    unsigned int saved_source_0x18;
    unsigned char unknown_0x1c_0x23[8];
    volatile unsigned int copy_0x24;
    unsigned char unknown_0x28_0x2b[4];
    volatile unsigned int cleared_0x2c;
};

void pvz_02027ba4_snapshot(struct UnknownState *state)
{
    state->copy_0x24 = state->saved_source_0x18;
    state->cleared_0x2c = 0;
}
