/* arm9:020469c4
 * Copy an 8-byte (two word) pair from src to dst.
 * The original loads both source words before storing both destination
 * words, which a struct assignment reproduces exactly.
 */
struct Pair {
    unsigned int first;   /* +0x0 */
    unsigned int second;  /* +0x4 */
};

void copy_pair(struct Pair *dst, struct Pair *src)
{
    *dst = *src;
}
