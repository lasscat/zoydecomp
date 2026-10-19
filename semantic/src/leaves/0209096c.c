/* Stores a constant 1 and the argument into consecutive fields.  The pointer is
   volatile so the original's two independent stores and their order are kept. */
void set_pair(volatile unsigned *p, unsigned v)
{
    p[1] = 1;
    p[2] = v;
}
