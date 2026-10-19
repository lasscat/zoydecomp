typedef struct {
    unsigned char pad[0x3a];
    volatile unsigned short flag;
} LowRegisters;

void wait_flag_clear(unsigned mask)
{
    LowRegisters *regs = (LowRegisters *)0x020ff5a0;

    while (regs->flag & mask) {
    }
}
