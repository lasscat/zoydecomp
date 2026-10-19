/* Stores the argument and a tail pointer (or null) in two fields. */
void pvz_020b1e54_leaf(unsigned *p, unsigned v)
{
    p[1] = v;
    p[2] = v ? v + 0xc : 0;
}
