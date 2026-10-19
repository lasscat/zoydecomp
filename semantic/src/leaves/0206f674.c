/* arm9:0206f674
 * Resets one of two representations of a small object, chosen by the top
 * bit of the first word.
 *   bit31 clear : obj[0] &= 1, obj[1] = 0
 *   bit31 set   : *obj[+8] = 0, obj[+4] = 0
 */
void sub_0206f674(char *obj)
{
    unsigned int flag = (*(unsigned int *)obj << 31) >> 31;

    if (flag == 0) {
        unsigned char b = (unsigned char)obj[0];

        obj[1] = 0;
        obj[0] = (char)(b & 0x01u);
    } else {
        *(char *)*(char **)(obj + 8) = 0;
        *(unsigned int *)(obj + 4) = 0;
    }
}
