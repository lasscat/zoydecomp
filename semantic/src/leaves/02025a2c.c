typedef struct {
    int a;
    int b;
    int c;
    int d;
} Entry;

typedef struct {
    char *name;
    int *value;
    int *limit;
    int pad0;
    int pad1;
    int pad2;
    Entry *entries;
} Object;

void add_entry(Object *obj, int offset, int extra)
{
    Entry *e = (Entry *)((char *)obj->entries + offset);

    e->a = (int)obj->value;
    e->b = (int)obj->name;
    e->c = (int)obj->limit;
    if (*obj->name != '*') {
        e->d = (int)obj->value + extra;
        return;
    }
    e->d = (int)(e + 1);
    e[1].a = *(int *)obj->value + extra;
}
