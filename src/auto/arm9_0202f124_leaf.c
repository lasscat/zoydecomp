/* When owner+0x00 holds a target pointer, sets that target's 16-bit flags at
 * +0x34 to 1 and stores the supplied value at +0x38.  The pointer field is
 * volatile: the original reloads it independently for each use, so the field
 * must not be cached in a register (that reload order is the recorded value
 * effect of this helper, no memory-mapped hardware is implied). */
struct UnknownOwner {
    void *volatile target_0x00;
};

void pvz_0202f124_leaf(struct UnknownOwner *owner, unsigned short value)
{
    if (owner->target_0x00 != 0) {
        *(unsigned short *)((unsigned char *)owner->target_0x00 + 0x34) = 1;
        *(unsigned short *)((unsigned char *)owner->target_0x00 + 0x38) = value;
    }
}
