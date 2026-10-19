/* Rounds a field up to the next multiple of eight (signed division). */
int round_up_8(int *p)
{
    return (p[4] + 7) / 8;
}
