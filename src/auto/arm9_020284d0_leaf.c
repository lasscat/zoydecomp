/* Two-level pointer chase: [ [p+4] ]. */
int pvz_020284d0_leaf(char *p)
{
    int *q = *(int **)(p + 4);
    return *q;
}
