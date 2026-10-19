/* Fixed-point scale: (x * 12808) >> 12. */
int scale_fixed(int x)
{
    return x * 12808 >> 12;
}
