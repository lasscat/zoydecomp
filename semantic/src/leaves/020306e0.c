/* Entry `index` of the 16-byte-stride table reached through 0x02104240. */
char *func_020306e0(unsigned int index) {
    char *g = *(char **)0x02104240u;
    char *t = *(char **)(g + 0x90);
    if (index >= *(unsigned int *)(t + 8))
        return 0;
    return *(char **)(t + index * 16 + 0x14);
}
