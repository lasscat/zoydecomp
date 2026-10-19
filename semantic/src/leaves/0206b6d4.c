/* Initialises an object from a global pointer table.
 * object offsets (unknown names documented):
 *   0x00 : int, copy of *global
 *   0x04 : int, field 0x5fc of that global
 *   0x08..0x14 : int, zeroed
 *   0x18 : unsigned char, 1
 *   0x1c : int, -1
 *   0x20 : int, 400000
 */
struct obj {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
    unsigned char f18;
    char pad_19[3];
    int f1c;
    int f20;
};

void obj_init(struct obj *o)
{
    o->f08 = 0;
    o->f0c = 0;
    o->f10 = 0;
    o->f14 = 0;
    o->f18 = 1;
    o->f1c = -1;
    o->f20 = 400000;

    int global = *(int *)0x021069f4u;
    o->f00 = global;
    o->f04 = *(int *)(global + 0x5fc);
}
