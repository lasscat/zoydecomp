/* Stores the argument and a tail pointer (or null) in two fields. */
void set_with_tail(unsigned *p, unsigned v)
{
    p[1] = v;
    p[2] = v ? v + 0xc : 0;
}
