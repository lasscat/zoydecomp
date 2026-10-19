/* arm9:0202e63c - pick LCD transfer block sizes for one of the four engines. */

void lcd_block_size(unsigned int *out0, unsigned int *out1, int index)
{
    void **table = (void **)0x020d48e0u;
    void **entry = table;
    unsigned short hw;
    int bits;
    unsigned int mode;
    int port = index & 3;
    unsigned int shared;

    entry += index;
    hw = *(const unsigned short *)*entry;
    bits = (hw & 0xC000) >> 14;

    if (index <= 3)
        mode = *(volatile unsigned int *)0x04000000u;
    else
        mode = *(volatile unsigned int *)0x04001000u;
    mode &= 7u;

    if (port == 2) {
        if (mode == 2u || mode >= 4u) {
            shared = 0x10u << bits;
            *out0 = shared;
            *out1 = shared;
            return;
        }
    } else if (port == 3) {
        if (mode >= 1u) {
            shared = 0x10u << bits;
            *out0 = shared;
            *out1 = shared;
            return;
        }
    }

    *out0 = (bits & 1) ? 0x40u : 0x20u;
    *out1 = (bits & 2) ? 0x40u : 0x20u;
}
