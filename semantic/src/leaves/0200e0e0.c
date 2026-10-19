/* Combines three base-60 fields into a single count. */
int base60_total(int *t)
{
    return (t[0] * 60 + t[1]) * 60 + t[2];
}
