/* 0x02015e48: length of a zero-terminated halfword string. */
int WideStringLength(const unsigned short *text)
{
    int count = 0;

    while (*text++ != 0)
        count++;
    return count;
}
