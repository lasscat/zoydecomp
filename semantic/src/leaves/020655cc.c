/* Consumes up to the requested amount from the counter at p+0x5000+0xb00. */
int consume_amount(char *p, int amount)
{
    int *base = (int *)(p + 0x5000);
    if (amount <= base[0xb00 / 4]) {
        base[0xb00 / 4] -= amount;
        return 1;
    }
    return 0;
}
