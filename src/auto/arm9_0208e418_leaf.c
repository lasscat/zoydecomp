/* Fill one spawn slot and stamp the object it carries.

   The manager keeps 0x28-byte slots from +0x1B0; slot "index" receives the
   object pointer, its state word 0, a copy of the object's +0xC0 word, the
   nine caller words and finally the object's +0xC4 stamp, after which the
   object's flag word +0x168 gets bit 1 set. */
struct unit {
    char pad0[0xc0];
    int field_c0;
    int field_c4;
    char pad1[0x168 - 0xc8];
    int field_168;
};

struct entry {
    struct unit *object;
    int state;
    int field08;
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    int field20;
    int field24;
};

struct world {
    char pad[0x1b0];
    struct entry entries[1];
};

void pvz_0208e418_leaf(struct world *w, int index, struct unit *object, int x4, int x5, int x6,
                       int x7, int x8, int x9, int x10)
{
    w->entries[index].object = object;
    w->entries[index].field10 = x4;
    w->entries[index].field14 = x5;
    w->entries[index].field18 = x6;
    w->entries[index].field1c = x7;
    w->entries[index].field20 = x8;
    w->entries[index].field24 = x10;
    w->entries[index].field0c = x9;
    w->entries[index].state = 0;
    w->entries[index].field08 = w->entries[index].object->field_c0;
    w->entries[index].object->field_c4 = 0x64000;
    w->entries[index].object->field_168 |= 2;
}
