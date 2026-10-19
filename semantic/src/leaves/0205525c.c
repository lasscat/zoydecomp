/* Clear a header word pair plus the following 0x22-word array. */
void clear_table(unsigned *p)
{
    int i;

    p[0] = 0;
    p[1] = 0;

    for (i = 0; i < 0x22; i++)
        p[i + 2] = 0;
}
