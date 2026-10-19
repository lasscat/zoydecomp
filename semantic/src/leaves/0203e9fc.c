/* Dereference self; if the resulting pointer is non-null, return its first
   word, else return 0. */
unsigned int f(void **self) {
    unsigned int v = (unsigned int)*self;
    if (v == 0u)
        return 0u;
    return *(unsigned int *)v;
}
