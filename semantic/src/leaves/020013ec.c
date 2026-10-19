/* Fixed-point transform setup.  s[0..3] hold a packed rotation/scale pair of
   20-bit coefficients; the first two output words pack the truncated
   coefficients as two halfwords each, the last two hold the translated
   origin shifted back into 12.4 fixed point. */

void xform_set(int *out, int *s, int a, int b, int c, int d)
{
    int da = c - a;
    int db = d - b;
    int m00 = (s[0] << 12) >> 16;
    int m01 = (s[1] << 12) >> 16;
    int m10 = (s[2] << 12) >> 16;
    int m11 = (s[3] << 12) >> 16;

    out[0] = ((m01 & 0xffff) << 16) | (m00 & 0xffff);
    out[1] = ((m11 & 0xffff) << 16) | (m10 & 0xffff);
    out[2] = (s[0] * da + s[1] * db + (a << 12)) >> 4;
    out[3] = (s[2] * da + s[3] * db + (b << 12)) >> 4;
}
