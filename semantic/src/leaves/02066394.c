/* Hit test of point (x, y) against an axis-aligned rectangle plus a radius.
 * rect holds signed 16-bit fields: +0 left, +2 top, +4 width, +6 height.
 * Returns 1 when the point is inside the rectangle, or when it is outside on
 * both axes but within `radius` of the nearest corner, otherwise 0. */
int sub_02066394(int x, int y, int radius, const short *rect)
{
    int left = rect[0];
    int xdist = 0;
    int ydist = 0;
    int xout = 0;
    int yout = 0;

    if (x < left) {
        xdist = left - x;
        xout = 1;
    } else {
        int right = left + rect[2];

        if (x > right) {
            xdist = (x - left) - rect[2];
            xout = 1;
        }
    }

    if (y < rect[1]) {
        ydist = rect[1] - y;
        yout = 1;
    } else {
        int bottom = rect[1] + rect[3];

        if (y > bottom) {
            ydist = (y - rect[1]) - rect[3];
            yout = 1;
        }
    }

    if (!xout && !yout)
        return 1;
    if (xout && yout) {
        if (ydist * ydist + xdist * xdist <= radius * radius)
            return 1;
        return 0;
    }
    if (xout) {
        if (xdist > radius)
            return 0;
        return 1;
    }
    if (ydist > radius)
        return 0;
    return 1;
}
