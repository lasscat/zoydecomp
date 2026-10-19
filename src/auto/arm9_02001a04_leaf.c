/* arm9:02001a04 -- reads the display control word at 0x04001000 and returns the
 * VRAM block base for the current mode (0x06200000 + ((flags & 0x3c) >> 2 << 14)),
 * or 0 for modes 3..5 whose flag bit 7 is set.  Reconstructed exactly. */
typedef unsigned int u32;
typedef unsigned short u16;

int pvz_02001a04_leaf(void)
{
    volatile u32 *regs = (volatile u32 *)0x04001000;
    int mode;
    u16 flags;

    mode = (int)(*regs & 7);
    flags = *(volatile u16 *)(0x04001000 + 0x0e);
    if (mode < 3 || (mode < 6 && (flags & 0x80) == 0))
        return (int)((((u32)flags & 0x3c) >> 2 << 14) + 0x06200000);
    return 0;
}
