/* Reports whether the flag selected by `bit` is set in `flags`. */
int pvz_020528f0_test_bit(unsigned int flags, unsigned int bit)
{
    return (flags & (1u << bit)) != 0;
}
