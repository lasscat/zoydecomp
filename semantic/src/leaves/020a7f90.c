/* True when the counter at +0x50 differs from the word at [[p+4]+0x168]. */
int func_020a7f90(char *p) {
    char *q = *(char **)(p + 4);
    unsigned int a = *(unsigned int *)(p + 0x50);
    unsigned int b = *(unsigned int *)(q + 0x168);
    return a != b ? 1 : 0;
}
