/*
 * Clears three consecutive 32-bit words starting at field +8 of self
 * (offsets +8, +0xC, +0x10 unverified).
 */
void clear_three(int *self)
{
    int i;

    for (i = 0; i < 3; i++)
        *(int *)((char *)self + 8 + i * 4) = -1;
}
