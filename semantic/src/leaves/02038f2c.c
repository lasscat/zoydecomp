/* Clear a small 3-word vector. */
void clear3(unsigned *v)
{
    unsigned i;

    for (i = 0; i < 3; i++)
        v[i] = 0;
}
