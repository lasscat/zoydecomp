/* Publish the movement of a four-component position vector.

   The live components at +0x3C..+0x48 are read into registers, the delta
   against the previous sample at +0xD8..+0xE4 is written to the movement
   fields at +0xE8..+0xF4 and the previous sample is then replaced by the
   current one. */
struct motion {
    char pad0[0x3c];
    int x;
    int y;
    int z;
    int w;
    char pad1[0xd8 - 0x4c];
    int last_x;
    int last_y;
    int last_z;
    int last_w;
    int dx;
    int dy;
    int dz;
    int dw;
};

void update_motion(struct motion *m)
{
    int x = m->x;
    int y = m->y;
    int z = m->z;
    int w = m->w;

    m->dx = x - m->last_x;
    m->dy = y - m->last_y;
    m->dz = z - m->last_z;
    m->dw = w - m->last_w;
    m->last_x = x;
    m->last_y = y;
    m->last_z = z;
    m->last_w = w;
}
