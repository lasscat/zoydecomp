void f(unsigned int flags)
{
    if (flags & 1)
        *(volatile unsigned char *)0x04000240 = 0x80;
    if (flags & 2)
        *(volatile unsigned char *)0x04000241 = 0x80;
    if (flags & 4)
        *(volatile unsigned char *)0x04000242 = 0x80;
    if (flags & 8)
        *(volatile unsigned char *)0x04000243 = 0x80;
    if (flags & 0x10)
        *(volatile unsigned char *)0x04000244 = 0x80;
    if (flags & 0x20)
        *(volatile unsigned char *)0x04000245 = 0x80;
    if (flags & 0x40)
        *(volatile unsigned char *)0x04000246 = 0x80;
    if (flags & 0x80)
        *(volatile unsigned char *)0x04000248 = 0x80;
    if (flags & 0x100)
        *(volatile unsigned char *)0x04000249 = 0x80;
}
