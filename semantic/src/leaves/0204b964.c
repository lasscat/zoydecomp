typedef struct Rect {
    int r00, r04, r08, r0c, r10, r14, r18, r1c, r20, r24, r28;
    int minX;   /* 0x2c */
    int minY;   /* 0x30 */
    int height; /* 0x34 */
    int width;  /* 0x38 */
} Rect;

/* Point-in-rectangle test: x must lie inside [minX, minX + height) and y
   inside [minY, minY + width). */

int rect_contains(Rect *r, int x, int y)
{
    int hit = 0;
    int inY = 0;
    int inX = 0;

    if (x >= r->minX) {
        if (x < r->minX + r->height)
            inX = 1;
    }
    if (inX) {
        if (y >= r->minY)
            inY = 1;
    }
    if (inY) {
        if (y < r->minY + r->width)
            hit = 1;
    }
    return hit;
}
