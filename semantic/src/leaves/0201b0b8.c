/* 0x0201b0b8: three-way byte comparison limited to n bytes.
 * Only the sign of the difference is reported (-1 or 1), 0 when equal. */
int ByteCompareN(const unsigned char *left, const unsigned char *right, unsigned int n)
{
    while (n != 0)
    {
        unsigned char a = *left++;
        unsigned char b = *right++;
        if (a != b)
            return a < b ? -1 : 1;
        n--;
    }
    return 0;
}
