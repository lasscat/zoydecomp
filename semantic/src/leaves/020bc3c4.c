/* arm9:020bc3c4
 * Seeds a 624 entry state table: table[0] takes the seed and every following
 * entry is 1812433253 * (previous ^ (previous >> 30)) + index.  The trailer
 * words at +0x9C0, +0x9C4, +0x9C8 and +0x9D4 are then set to 0, 1, 0 and 0.
 */
void state_seed(unsigned int *state, unsigned int seed)
{
    unsigned int i;
    unsigned int value = seed;

    state[0] = seed;
    i = 1;
    do {
        value = 1812433253u * (value ^ (value >> 30)) + i;
        state[i] = value;
        i++;
    } while (i < 624);
    state[624] = 0;
    state[625] = 1;
    state[626] = 0;
    state[629] = 0;
}
