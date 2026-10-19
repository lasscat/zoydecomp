/*
 * Sets or clears bit 0 of the 32-bit field at +8 of self, leaving the other
 * bits untouched. Offset +8 is an unverified field offset.
 */
void pvz_0203ef6c_leaf(int *self, int on)
{
    if (on)
        *(unsigned int *)((char *)self + 8) |= 1;
    else
        *(unsigned int *)((char *)self + 8) &= ~1u;
}
