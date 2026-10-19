/* Reports whether the flag selected by `bit` is set in `flags`. */
int pvz_020528f0_leaf(unsigned int flags, unsigned int bit) { return (flags & (1u << bit)) != 0; }
