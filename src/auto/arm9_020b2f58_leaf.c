int pvz_020b2f58_leaf(int *obj, int index)
{
    return *(unsigned short *)((char *)obj[3] + index * 4) & ~0xff00;
}
