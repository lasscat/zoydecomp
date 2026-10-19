/* arm9:0207126c
 * Fixed-point scale: (value * 3416) >> 12, i.e. a 12-bit fraction.
 * 3416 (0xD58) comes from a literal pool in the original.
 */
int scale_by_fraction(int value)
{
    return (value * 3416) >> 12;
}
