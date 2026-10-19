/* Initialises a six-word block: vtable-like pointer, zeroed fields, count 0x15. */
void init_six(void **p)
{
    p[0] = (void *)0x020e1758u;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = (void *)0x15;
}
