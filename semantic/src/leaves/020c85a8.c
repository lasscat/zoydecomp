/* Clears three words and one byte of the object at 0x021DE480. */
void func_020c85a8(void) {
    char *p = (char *)0x021DE480u;
    *(int *)(p + 0x18) = 0;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x0C) = 0;
    *(unsigned char *)(p + 1) = 0;
}
