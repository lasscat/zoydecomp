/* True when bit 0 of the word at +8 is set. */
int func_0203ef58(char *p) {
    return (*(unsigned int *)(p + 8) & 1) ? 1 : 0;
}
