/* Pick an id: 0 when a is set, otherwise 3, or 2 when b is clear. */
int sub_020c2d70(int a, int b)
{
    if (a != 0)
        return 0;

    return b == 0 ? 2 : 3;
}
