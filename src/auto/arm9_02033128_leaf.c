/* arm9:02033128
 * Advances the signed 32-bit cursor at +8 while it is strictly below the
 * limit at +0xc.
 */
struct cursor {
    int unused0; /* +0x0 */
    int unused1; /* +0x4 */
    int index;   /* +0x8 */
    int limit;   /* +0xc */
};

void pvz_02033128_leaf(struct cursor *cursor)
{
    if (cursor->index < cursor->limit)
        cursor->index = cursor->index + 1;
}
