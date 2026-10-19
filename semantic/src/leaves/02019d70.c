/* Length of a NUL-terminated byte string, scanned a word at a time.

   Leading bytes are examined one at a time until the pointer becomes
   four-byte aligned (or a zero byte is met).  Whole words are then tested
   for a zero byte with the 0x7F7F7F7F mask: ((v & mask) + mask) | v | mask
   has a clear top bit in every byte that is zero, so the complement is
   zero exactly while the word holds no zero byte.  Once a word does hold
   one, the remaining bytes are counted one at a time.  The length is kept
   as a byte index. */
unsigned string_length(const char *s)
{
    unsigned i = 0;
    unsigned v;

    if ((unsigned)s & 3) {
        do {
            if (s[i] == 0)
                return i;
            i++;
        } while (((unsigned)s + i) & 3);
    }
    for (;;) {
        v = *(const unsigned *)(s + i);
        if (~(((v & 0x7f7f7f7f) + 0x7f7f7f7f) | v | 0x7f7f7f7f))
            break;
        i += 4;
    }
    while (s[i] != 0)
        i++;
    return i;
}
