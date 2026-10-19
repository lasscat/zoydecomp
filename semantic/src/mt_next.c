/* Independently reconstructed from BWBE-r0 ARM9 0x02034fc0.
 * Behavioral reference: ruslan831/PlantsVsZombies-decompilation
 * 325b2229a7225d73870bb69322eefcda3a45bf8d,
 * SexyAppFramework/MTRand.cpp, MTRand::NextNoAssert().
 * Algorithm attribution: Makoto Matsumoto and Takuji Nishimura, 1997-2002.
 * Full donor/file-specific notices accompany the connected seed draft in
 * NOTICE-MT.txt. The DS separates the raw 32-bit value (this function) from a
 * 31-bit non-negative wrapper at ARM9 0x02034fb0; the reference masks inside
 * NextNoAssert instead. Raw output and state layout come from the DS binary.
 * Research draft: no byte-match acceptance or semantic-equivalence proof.
 */
typedef unsigned int u32;

#ifndef PVZ_MT_STATE_DEFINED
#define PVZ_MT_STATE_DEFINED
struct PvzMtState {
    u32 remaining;    /* +0x000: outputs left before the next twist reload */
    u32 next_address; /* +0x004: raw 32-bit address of the next state word */
    u32 words[624];   /* +0x008: MT19937 state vector */
};
#endif

#define PVZ_MT_UPPER 0x80000000u
#define PVZ_MT_LOWER 0x7fffffffu
#define PVZ_MT_MATRIX_A 0x9908b0dfu

u32 pvz_mt_next(struct PvzMtState *state)
{
    u32 *words;
    u32 *next;
    u32 y;
    int kk;

    if (--state->remaining == 0) {
        /* Reload the whole vector when the counter drains. The DS stores the
         * next word address explicitly rather than an index; on a 32-bit DS
         * this 32-bit field is that pointer. */
        words = state->words;
        state->remaining = 624;
        state->next_address = (u32)(unsigned long)words;
        for (kk = 0; kk < 624 - 397; ++kk) {
            y = (words[kk] & PVZ_MT_UPPER) | (words[kk + 1] & PVZ_MT_LOWER);
            words[kk] = words[kk + 397] ^ (y >> 1)
                        ^ ((y & 1u) ? PVZ_MT_MATRIX_A : 0u);
        }
        for (; kk < 623; ++kk) {
            y = (words[kk] & PVZ_MT_UPPER) | (words[kk + 1] & PVZ_MT_LOWER);
            words[kk] = words[kk - 227] ^ (y >> 1)
                        ^ ((y & 1u) ? PVZ_MT_MATRIX_A : 0u);
        }
        y = (words[623] & PVZ_MT_UPPER) | (words[0] & PVZ_MT_LOWER);
        words[623] = words[396] ^ (y >> 1) ^ ((y & 1u) ? PVZ_MT_MATRIX_A : 0u);
    }

    next = (u32 *)(unsigned long)state->next_address;
    y = *next;
    state->next_address = (u32)(unsigned long)(next + 1);
    y ^= y >> 11;
    y ^= (y << 7) & 0x9d2c5680u;
    y ^= (y << 15) & 0xefc60000u;
    y ^= y >> 18;
    return y;
}
