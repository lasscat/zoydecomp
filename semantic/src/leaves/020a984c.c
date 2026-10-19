/* Reports whether the second argument lies in [10, 12].  The first argument is
   unused by the original (the value arrives in r1). */
int in_range_10_12(int unused, unsigned value)
{
    (void)unused;
    return (value - 10) <= 2;
}
