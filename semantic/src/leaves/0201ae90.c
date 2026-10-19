struct W { unsigned int a, b; };

int f(struct W v)
{
    if ((v.b & 0x7FF00000u) == 0) {
        if ((v.b & 0x000FFFFFu) || v.a)
            return 5;
        return 3;
    }
    if ((v.b & 0x7FF00000u) == 0x7FF00000u) {
        if ((v.b & 0x000FFFFFu) || v.a)
            return 1;
        return 2;
    }
    return 4;
}
