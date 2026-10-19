/* arm9:020493ec
 * Copy an 8-byte (two word) pair from src to dst.
 * Identical body to arm9:020469c4 (same target hash); struct assignment
 * reproduces the original load-both-then-store-both order.
 */
struct Pair {
    unsigned int first;   /* +0x0 */
    unsigned int second;  /* +0x4 */
};

void copy_pair(struct Pair *dst, struct Pair *src)
{
    *dst = *src;
}
