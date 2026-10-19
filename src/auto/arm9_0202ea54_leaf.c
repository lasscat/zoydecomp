/* Address of the element selected by the 16-bit index at array+0x0a;
 * elements are 16 bytes and the base pointer is array+0x00. */
struct UnknownArray {
    unsigned char *elements_0x00;
    unsigned char unknown_0x04_0x09[6];
    unsigned short selected_0x0a;
};

unsigned char *pvz_0202ea54_leaf(struct UnknownArray *array)
{
    return array->elements_0x00 + array->selected_0x0a * 16;
}
