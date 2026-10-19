/* Clears the pointee and then the pointer itself when the pointer is
   non-null.  The pointed-to slot is read through a volatile-qualified
   pointer so that the original's two independent loads of *p (one for the
   null test, one for the body) are reproduced; the object itself is not
   volatile. */
void pvz_0202efcc_leaf(int *volatile *p)
{
    if (*p != 0) {
        **p = 0;
        *p = 0;
    }
}
