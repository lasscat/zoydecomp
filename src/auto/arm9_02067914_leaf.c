/* Select one of two pointers held by a game object.

   The object has a pointer at +0xb8 whose target carries a kind tag at
   +0x658.  Only when that tag is 0x50 does the selection look at the global
   manager pointer at 0x02107F90: if its field at +0x6e4 equals the requested
   id, the pointer at +0x16c is returned, otherwise the one at +0x168.  For
   every other tag the object's +0x168 pointer is returned. */
struct object_kind {
    char pad[0x658];
    int tag;
};

struct object_manager {
    char pad[0x6e4];
    int current_id;
};

struct game_object {
    char pad0[0xb8];
    struct object_kind *kind;
    char pad1[0x168 - 0xbc];
    void *data_168;
    void *data_16c;
};

void *pvz_02067914_leaf(struct game_object *object, int id)
{
    if (object->kind->tag == 0x50)
        return (*(struct object_manager **)0x02107F90u)->current_id == id ? object->data_16c
                                                                          : object->data_168;
    return object->data_168;
}
