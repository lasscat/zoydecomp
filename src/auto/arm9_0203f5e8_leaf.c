/* Takes and clears the word field at offset 4. */
unsigned pvz_0203f5e8_leaf(unsigned *p)
{
    unsigned v = p[1];
    p[1] = 0;
    return v;
}
