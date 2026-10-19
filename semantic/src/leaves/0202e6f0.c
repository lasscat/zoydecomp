/* True when the halfword at +0xC equals the word at +4. */
int func_0202e6f0(char *p) {
    unsigned int a = *(unsigned short *)(p + 0xC);
    unsigned int b = *(unsigned int *)(p + 4);
    return a == b ? 1 : 0;
}
