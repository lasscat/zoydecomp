void f(int base, int value, int slot, int *s)
{
    int *q = (int *)((char *)base + 0xC4C + slot * 200);

    q[s[0]] = value;
    s[0] = s[0] + 1;
    if (s[0] < 0x32)
        q[s[0]] = -1;

    s[1] = s[1] - *(int *)(0x020D4B98 + value * 0x1C + 8);
    ((int *)((char *)s + 8))[value] = ((int *)((char *)s + 8))[value] + 1;
    ((int *)((char *)s + 0x90))[value] = ((int *)((char *)s + 0x90))[value] + 1;
}
