typedef struct Obj {
    int r00, r04, r08, r0c, r10, r14, r18, r1c, r20, r24, r28, r2c, r30, r34, r38, r3c;
    int r40, r44, r48, r4c, r50, r54, r58, r5c, r60, r64, r68, r6c, r70, r74, r78, r7c;
    int r80, r84, r88;
    unsigned int kind;      /* 0x8c */
} Obj;

int obj_lookup(Obj *o)
{
    switch (o->kind) {
    case 1:  case 2:  case 3:  case 4:  case 5:
    case 6:  case 7:  case 8:  case 9:  case 10:
    case 11: case 12: case 13: case 14: case 15:
    case 17: case 18: case 19:
        return *(int *)0x02108758;
    case 16:
        return *(int *)0x02108760;
    default:
        return *(int *)0x02108760;
    }
}
