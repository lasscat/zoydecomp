/* Packs the four words at +0,+4,+8,+0xC into one word at byte positions
   2,1,0,3. */
unsigned int func_02038fc0(char *p) {
    unsigned int a = *(unsigned int *)(p + 0);
    unsigned int b = *(unsigned int *)(p + 4);
    unsigned int c = *(unsigned int *)(p + 8);
    unsigned int d = *(unsigned int *)(p + 0xC);
    return (a << 16) | (b << 8) | c | (d << 24);
}
