/*
 * Locates the first occurrence of a NUL-terminated pattern inside a
 * NUL-terminated string and returns a pointer to it, or NULL when absent.
 * A NULL or empty pattern returns the haystack unchanged (no NULL guard on
 * the returned pointer is documented by the caller).
 */
char *find_pattern(char *text, const char *pattern)
{
    char first;

    if (pattern == 0 || (first = *pattern) == 0)
        return text;

    for (;;) {
        char sc = *text;

        if (sc == 0)
            return 0;

        if (sc == first) {
            const char *p = pattern + 1;
            char *t = text + 1;
            char pc, tc;

            for (;;) {
                pc = *p++;
                tc = *t++;

                if (tc != pc)
                    break;
                if (tc == 0)
                    break;
            }

            if (pc == 0)
                return text;
        }

        text++;
    }
}
