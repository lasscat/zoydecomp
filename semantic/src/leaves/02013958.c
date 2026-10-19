/* Record a pair of coordinates on a board object.
   self->ext (offset 0) points at a header whose dword at +4 is a kind tag;
   when that tag is 4 or 6 nothing is written.  The two coordinates are
   shortened by 14 and stored as 16-bit values at 0x2f2 and 0x2f0. */
struct board {
    unsigned char pad[0x2F0];
    short c2f0;
    short c2f2;
};

int board_set_coords(struct board *self, int a, int b)
{
    int *ext = *(int **)self;

    if (ext != 0)
        ext = (int *)((char *)ext + 4);

    if (ext != 0 && (*ext == 4 || *ext == 6))
        return 0;

    self->c2f2 = (short)(a - 14);
    self->c2f0 = (short)(b - 14);
    return 0;
}
