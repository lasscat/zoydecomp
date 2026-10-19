void pvz_021006bc_leaf(unsigned int addr, unsigned int *out, int len)
{
    unsigned int v;
    unsigned int ctrl;
    int off;
    unsigned char *cmd;
    unsigned int st;
    unsigned int d;

    v = *(volatile unsigned int *)0x02fffe60;
    ctrl = (v & ~0x07000000) | 0xa1000000;
    off = -(int)(addr & 0x1ff);
    while (*(volatile unsigned int *)0x040001a4 & 0x80000000)
        ;
    *(volatile unsigned char *)0x040001a1 = 0x80;
    addr += off;
    if (off >= len)
        return;
    cmd = (unsigned char *)0x040001a1;
    for (;;) {
        cmd[7] = 0xb7;
        cmd[8] = (unsigned char)(addr >> 24);
        cmd[9] = (unsigned char)(addr >> 16);
        cmd[10] = (unsigned char)(addr >> 8);
        cmd[11] = (unsigned char)addr;
        cmd[12] = 0;
        cmd[13] = 0;
        cmd[14] = 0;
        *(volatile unsigned int *)(cmd + 3) = ctrl;
        do {
            st = *(volatile unsigned int *)(cmd + 3);
            if (st & 0x800000) {
                d = *(volatile unsigned int *)0x04100010;
                if (off >= 0 && off < len)
                    *(unsigned int *)((unsigned char *)out + off) = d;
                off += 4;
            }
        } while (st & 0x80000000);
        addr += 0x200;
        if (off >= len)
            return;
    }
}
