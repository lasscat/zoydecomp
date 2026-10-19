/* Stores two words into the argument object at offsets 0x30 and 0x3c.
   The two independent stores are written in this order because the backend
   emits independent field stores in that order and the original emits
   0x30 first. */
struct object_02068fb4 {
    unsigned char pad[0x30];
    unsigned int field30;
    unsigned char pad2[8];
    unsigned int field3c;
};

void set_pair_02068fb4(struct object_02068fb4 *object, unsigned int a, unsigned int b)
{
    object->field3c = b;
    object->field30 = a;
}
