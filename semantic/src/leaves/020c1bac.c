/* Fixed point scale: (value * 0x320a) >> 12, with the original 32x32 low
 * product and an arithmetic shift. */
int pvz_020c1bac_scale(int value)
{
    return (value * 0x320a) >> 12;
}
