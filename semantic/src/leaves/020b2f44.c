/* Reads the high 16-bit half of one 32-bit pair entry, low byte only. */
typedef struct {
    unsigned short lo;
    unsigned short hi;
} Pair;

typedef struct {
    int f0;
    int f1;
    int f2;
    Pair *pairs;
} Obj;

unsigned low_byte_at(Obj *o, int i)
{
    return o->pairs[i].hi & ~0xff00u;
}
