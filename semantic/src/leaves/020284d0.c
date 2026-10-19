/* Two-level pointer chase: [ [p+4] ]. */
int func_020284d0(char *p) {
    int *q = *(int **)(p + 4);
    return *q;
}
