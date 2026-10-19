/* arm9:020a8814 - containment test for a rectangle described by origin + extents. */

typedef struct {
    int reserved0;
    int reserved1;
    int left;
    int top;
    int width;
    int height;
} Rect;

int rect_contains(const Rect *r, int x, int y)
{
    int result = 0;
    int below_top = 0;
    int inside_x = 0;

    if (x >= r->left)
        inside_x = x < r->left + r->width;

    if (inside_x && y >= r->top)
        below_top = 1;

    if (below_top && y < r->top + r->height)
        result = 1;

    return result;
}
