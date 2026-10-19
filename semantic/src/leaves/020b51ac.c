/* Initialises a five word object: the vtable word 0x020e9994 followed by the
   four arguments (the fifth argument arrives on the stack). */
struct object_020b51ac {
    void *vtable;
    unsigned int field4;
    unsigned int field8;
    unsigned int fieldc;
    unsigned int field10;
};

void init_020b51ac(struct object_020b51ac *object, unsigned int a, unsigned int b,
                   unsigned int c, unsigned int d)
{
    object->vtable = (void *)0x020e9994;
    object->field4 = a;
    object->field8 = b;
    object->fieldc = c;
    object->field10 = d;
}
