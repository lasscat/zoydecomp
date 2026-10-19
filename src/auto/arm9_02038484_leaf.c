/* Structure initialiser for the object at r0: constant word 0x020e166c at 0, a
 * zero byte at 4, zero words at 8..0x2c, a zero byte at 0x38 and zero words at
 * 0x48..0x50.  Offsets 0x30..0x37 and 0x39..0x47 are left untouched (fields not
 * initialised here).
 *
 * The original writes every field in a strict program order and never reloads
 * them, so the pointer is volatile only to pin that exact store order (this is
 * the sole reason for the qualifier). */
void pvz_02038484_leaf(unsigned char *obj)
{
    volatile unsigned char *p = (volatile unsigned char *)obj;

    *(volatile unsigned int *)(p + 0x00) = 0x020e166c;
    p[0x04] = 0;
    *(volatile unsigned int *)(p + 0x08) = 0;
    *(volatile unsigned int *)(p + 0x0c) = 0;
    *(volatile unsigned int *)(p + 0x10) = 0;
    *(volatile unsigned int *)(p + 0x14) = 0;
    *(volatile unsigned int *)(p + 0x18) = 0;
    *(volatile unsigned int *)(p + 0x1c) = 0;
    *(volatile unsigned int *)(p + 0x20) = 0;
    *(volatile unsigned int *)(p + 0x24) = 0;
    *(volatile unsigned int *)(p + 0x28) = 0;
    *(volatile unsigned int *)(p + 0x2c) = 0;
    p[0x38] = 0;
    *(volatile unsigned int *)(p + 0x48) = 0;
    *(volatile unsigned int *)(p + 0x4c) = 0;
    *(volatile unsigned int *)(p + 0x50) = 0;
}
