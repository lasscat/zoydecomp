/*
 * Stores two 32-bit values into fields +0x54 and +0x58. If the second value
 * is zero the first is cleared and the second is left alone; otherwise a zero
 * first value clears the second. Keeps the pair mutually exclusive.
 * Offsets 0x54 and 0x58 are unverified field offsets in the owner object.
 */
void pvz_0200b8cc_leaf(int *self, int first, int second)
{
    if (second == 0)
        first = 0;
    else if (first == 0)
        second = 0;

    *(int *)((char *)self + 0x54) = first;
    *(int *)((char *)self + 0x58) = second;
}
