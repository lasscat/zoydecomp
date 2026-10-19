/* Research-only DS RNG lifecycle. No strict acceptance or compiler match.
 * Independently restated from the DS instructions and saved seed/next drafts.
 * Algorithm correspondence/attribution: systems/rng.md and NOTICE-MT.txt.
 * Names are operation/layout hypotheses, not a recovered desktop class.
 * The default pointer is controlled harness state; its real owner is unknown.
 */
typedef unsigned int u32;

struct PvzMtState {
    u32 remaining;
    u32 next_address;
    u32 words[624];
};

int pvz_mt_seed(struct PvzMtState *state, u32 seed)
{
    u32 index;
    if (seed == 0)
        return 0;
    state->words[0] = seed;
    for (index = 1; index < 624; ++index) {
        u32 previous = state->words[index - 1];
        state->words[index] = 1812433253U * (previous ^ (previous >> 30)) + index;
    }
    state->remaining = 1;
    return 1;
}

u32 pvz_mt_next(struct PvzMtState *state)
{
    u32 *words;
    u32 *next;
    u32 y;
    int kk;
    if (--state->remaining == 0) {
        words = state->words;
        state->remaining = 624;
        state->next_address = (u32)(unsigned long)words;
        for (kk = 0; kk < 624 - 397; ++kk) {
            y = (words[kk] & 0x80000000U) | (words[kk + 1] & 0x7fffffffU);
            words[kk] = words[kk + 397] ^ (y >> 1) ^ ((y & 1U) ? 0x9908b0dfU : 0U);
        }
        for (; kk < 623; ++kk) {
            y = (words[kk] & 0x80000000U) | (words[kk + 1] & 0x7fffffffU);
            words[kk] = words[kk - 227] ^ (y >> 1) ^ ((y & 1U) ? 0x9908b0dfU : 0U);
        }
        y = (words[623] & 0x80000000U) | (words[0] & 0x7fffffffU);
        words[623] = words[396] ^ (y >> 1) ^ ((y & 1U) ? 0x9908b0dfU : 0U);
    }
    next = (u32 *)(unsigned long)state->next_address;
    y = *next;
    state->next_address = (u32)(unsigned long)(next + 1);
    y ^= y >> 11;
    y ^= (y << 7) & 0x9d2c5680U;
    y ^= (y << 15) & 0xefc60000U;
    y ^= y >> 18;
    return y;
}

/* Original helper at 0x02034f94 reads BSS word 0x02105dfc for null input
 * and tail-branches to next. This extern is a native behavior-model input,
 * not permission for strict allocated data or arbitrary symbol resolution.
 */
extern struct PvzMtState *pvz_mt_default_state;

u32 pvz_mt_next_default(struct PvzMtState *state)
{
    if (state == 0)
        state = pvz_mt_default_state;
    return pvz_mt_next(state);
}

/* 0x02034fb0 calls the helper, then clears bit 31. */
u32 pvz_mt_next_nonnegative(struct PvzMtState *state)
{
    return pvz_mt_next_default(state) & 0x7fffffffU;
}
