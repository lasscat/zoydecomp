/* Stores a byte into the object referenced by the first word, if it is
   non-null.  The referenced pointer is volatile so the original's two
   independent reads of *p (test and store base) are kept. */
void pvz_0202f0b0_leaf(unsigned char *volatile *p, unsigned char v)
{
    if (*p)
        (*p)[0x40] = v;
}
