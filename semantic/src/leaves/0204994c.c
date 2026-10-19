/* arm9:0204994c
 * 8-byte (two word) structure copy; both source words are loaded before
 * either store, exactly like the original.
 */
struct pair8 {
    unsigned int first;
    unsigned int second;
};

void copy_pair8(struct pair8 *dst, const struct pair8 *src)
{
    *dst = *src;
}
