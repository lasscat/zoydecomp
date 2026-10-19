int record_low_half(int *obj, int index)
{
    return *(unsigned short *)((char *)obj[3] + index * 4) & ~0xff00;
}
