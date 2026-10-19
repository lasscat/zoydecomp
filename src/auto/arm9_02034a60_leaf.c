/* Preloads two tables that live inside a caller-supplied block. */
void pvz_02034a60_leaf(int *base)
{
    int i = 0x1001;

    do {
        ((int *)((char *)base + 0x901c))[i] = 0x1000;
        i++;
    } while (i <= 0x1100);

    i = 0;
    do {
        ((int *)((char *)base + 0x1014))[i] = 0x1000;
        i++;
    } while (i < 0x1000);
}
