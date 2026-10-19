/* arm9:021001a0 - fixed point cross product of two 3-vectors. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

void vec3_cross(const Vec3 *a, const Vec3 *b, Vec3 *out)
{
    out->x = (int)((((long long)a->y * b->z) - ((long long)a->z * b->y) + 0x800) >> 12);
    out->y = (int)((((long long)a->z * b->x) - ((long long)a->x * b->z) + 0x800) >> 12);
    out->z = (int)((((long long)a->x * b->y) - ((long long)a->y * b->x) + 0x800) >> 12);
}
