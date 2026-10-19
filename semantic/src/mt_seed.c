/* Independently reconstructed from BWBE-r0 ARM9 0x02034f40.
 * Behavioral reference: ruslan831/PlantsVsZombies-decompilation
 * 325b2229a7225d73870bb69322eefcda3a45bf8d,
 * SexyAppFramework/MTRand.cpp, MTRand::SRand(unsigned long).
 * Algorithm attribution: Makoto Matsumoto and Takuji Nishimura, 1997-2002.
 * Full donor/file-specific notices accompany this draft in NOTICE-MT.txt.
 * DS zero-seed behavior and state representation come from its own binary.
 * Research draft: no byte-match acceptance or semantic-equivalence proof.
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
    if (seed == 0) {
        return 0;
    }
    state->words[0] = seed;
    for (index = 1; index < 624; ++index) {
        u32 previous = state->words[index - 1];
        state->words[index] = 1812433253U * (previous ^ (previous >> 30)) + index;
    }
    state->remaining = 1;
    return 1;
}
