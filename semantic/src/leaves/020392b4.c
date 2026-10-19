/* 0x020392b4: initialize a six-word descriptor: the first word is a fixed
 * table pointer, the following five words are copied from src[1..5]. */
void InitDescriptor(unsigned int *dest, const unsigned int *src)
{
    dest[0] = 0x020E1758;
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
    dest[4] = src[4];
    dest[5] = src[5];
}
