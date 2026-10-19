/* When the word at +0 is 1, stores the halfword at +0x10 and sets bit 2 of
   the halfword at +0x12. */
void func_020295f0(char *p, unsigned int v) {
    if (*(int *)p == 1) {
        *(unsigned short *)(p + 0x10) = (unsigned short)v;
        *(unsigned short *)(p + 0x12) |= 4;
    }
}
