/* Returns the 16-bit field at +0x12 of the object at 0x020FD340. */
unsigned int func_02003b18(void) {
    unsigned char *base = (unsigned char *)0x020FD340u;
    return *(volatile unsigned short *)(base + 0x12);
}
