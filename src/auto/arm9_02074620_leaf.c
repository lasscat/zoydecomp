/* Clears the state word when it is 0x30 and the companion field is zero. */
void pvz_02074620_leaf(unsigned *p)
{
    if (p[0x3c / 4] == 0x30 && p[0x54 / 4] == 0)
        p[0x3c / 4] = 0;
}
