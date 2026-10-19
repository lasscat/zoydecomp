/* Selects a small state code from two arguments.
 * Unknown first argument (unused). When `flag` is non-zero the result is 0,
 * otherwise 3 when `zero` is non-zero and 2 when it is zero. */
int sub_020c3110(int unused, int flag, int zero)
{
    int result;

    if (flag != 0)
        return 0;
    result = 3;
    if (zero == 0)
        result = 2;
    return result;
}
