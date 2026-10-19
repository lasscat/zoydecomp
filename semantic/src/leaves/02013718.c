/* Release an intrusive free-list at offset 0, reset a set of bookkeeping
 * fields, and clear one byte in each of 16 records (stride 0x24, byte at
 * offset 0xae). */
void sub_02013718(unsigned char *obj, unsigned int value)
{
    unsigned int *node = *(unsigned int **)obj;
    unsigned int i;

    *(unsigned int *)(obj + 0x2ec) = 0xffffffffu;
    *(unsigned short *)(obj + 0x2f0) = 0;
    *(unsigned short *)(obj + 0x2f2) = 0;
    *(unsigned int *)(obj + 0x2f4) = 0;
    *(unsigned int *)(obj + 0xc) = value;

    while (node != 0) {
        *(unsigned int **)obj = (unsigned int *)node[0];
        node[1] = 0;
        node = *(unsigned int **)obj;
    }

    *(unsigned int *)(obj + 0x10) = 0;
    *(unsigned short *)(obj + 0x18) = 0;
    *(unsigned short *)(obj + 0x1a) = 0;

    for (i = 0; i < 16; i++)
        *(unsigned char *)(obj + i * 0x24 + 0xae) = 0;
}
