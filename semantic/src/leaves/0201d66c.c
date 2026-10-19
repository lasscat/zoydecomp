/* Bounded string copy: copies src into dst for at most n bytes, stopping after a
 * NUL terminator which is copied, then pads the remaining bytes with NUL. */
void sub_0201d66c(char *dst, const char *src, unsigned int n)
{
    if (n == 0)
        return;
    for (;;) {
        char c = *src++;
        *dst = c;
        if (*dst == 0) {
            if (--n == 0)
                return;
            dst++;
            do {
                *dst++ = 0;
            } while (--n != 0);
            return;
        }
        dst++;
        if (--n == 0)
            return;
    }
}
