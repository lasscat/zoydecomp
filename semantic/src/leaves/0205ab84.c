/* Point-in-rect test over a signed 16-bit rectangle.
 * Layout (unknown): p[0] x, p[1] y, p[2] width, p[3] height.
 */
int sub_0205ab84(const short *p, int a, int b)
{
    int in_a = 0;
    int in_b = 0;
    int res = 0;

    if (a >= p[0] && a < p[0] + p[2])
        in_a = 1;
    if (in_a && b >= p[1])
        in_b = 1;
    if (in_b && b < p[1] + p[3])
        res = 1;

    return res;
}
