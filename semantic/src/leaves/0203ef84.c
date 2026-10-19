void flag_copy(int *dst, const int *src)
{
    *dst = (*src & ~1) | (*dst & 1);
}
