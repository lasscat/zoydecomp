/* Copies the four words of the source record into the words at +0x0c through
 * +0x18 of the fixed global at 0x021d48f8. */
struct UnknownSource {
    unsigned int first_0x00;
    unsigned int second_0x04;
    unsigned int third_0x08;
    unsigned int fourth_0x0c;
};

struct UnknownDestination {
    unsigned char unknown_0x00_0x0b[0x0c];
    unsigned int first_0x0c;
    unsigned int second_0x10;
    unsigned int third_0x14;
    unsigned int fourth_0x18;
};

void pvz_020bf310_copy_four(struct UnknownSource *source)
{
    struct UnknownDestination *destination = (struct UnknownDestination *)0x021d48f8;

    destination->first_0x0c = source->first_0x00;
    destination->second_0x10 = source->second_0x04;
    destination->third_0x14 = source->third_0x08;
    destination->fourth_0x18 = source->fourth_0x0c;
}
