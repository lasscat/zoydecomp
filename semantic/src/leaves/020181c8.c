/* Two-level pointer chase: [ [0x02100BFC] + 8 ]. */
char *func_020181c8(void) {
    char *p = *(char **)(0x02100BF0u + 0xC);
    return *(char **)(p + 8);
}
