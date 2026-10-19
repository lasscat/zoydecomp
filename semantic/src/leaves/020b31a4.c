/* Bounds-checked fetch of one element of a two-dimensional grid.

   The grid holds its row count at +0x08, its column count at +0x0C and the
   cell array at +0x14.  A cell is addressed as col * rows + row.  The cell
   value is reported through *out and 1 is returned when the cell exists and
   is non-zero; otherwise *out is left alone and 0 is returned. */
struct grid {
    char pad0[8];
    int rows;
    int cols;
    char pad1[4];
    int *cells;
};

int grid_value(struct grid *g, int *out, int col, int row)
{
    int value;

    if (g->cells != 0 && col < g->cols && row < g->rows) {
        value = g->cells[col * g->rows + row];
        if (value != 0) {
            if (out != 0)
                *out = value;
            return 1;
        }
    }
    return 0;
}
