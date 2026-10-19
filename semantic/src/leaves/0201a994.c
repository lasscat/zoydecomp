/* 0201a994 (12 bytes): integer absolute value.
 *   cmp  r0, #0
 *   rsblt r0, r0, #0   ; r0 = 0 - r0 when r0 < 0
 *   bx   lr
 * Natural C: return the magnitude of a signed int. */
int leaf_abs(int value)
{
    return value < 0 ? -value : value;
}
