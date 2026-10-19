/* Stores the same address constant into two pointer fields and reports 1. */
int set_two_pointers(void **p)
{
    p[3] = (void *)0x020cd228u;
    p[4] = (void *)0x020cd228u;
    return 1;
}
