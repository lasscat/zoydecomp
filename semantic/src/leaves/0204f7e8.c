/* Initialise a structure: eight identical float-bit words (0xc61c4000 =
 * -10000.0f) at 0..0x1c, zero words at 0x24/0x20 and a pointer at 0x28. */
void sub_0204f7e8(unsigned char *obj)
{
    *(unsigned int *)(obj + 0x00) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x04) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x08) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x0c) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x10) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x14) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x18) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x1c) = 0xc61c4000u;
    *(unsigned int *)(obj + 0x24) = 0;
    *(unsigned int *)(obj + 0x20) = 0;
    *(unsigned int *)(obj + 0x28) = 0x020e3058;
}
