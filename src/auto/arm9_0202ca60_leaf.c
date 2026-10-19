/* Tests bit 0 of the flag word at offset 0x24. The original materialises the
   boolean with tst/movne/moveq; clang keeps the masked value itself and is one
   instruction shorter. */
struct object_0202ca60 {
    unsigned char pad[0x24];
    unsigned int flags;
};

int pvz_0202ca60_leaf(struct object_0202ca60 *object) { return (object->flags & 1) != 0; }
