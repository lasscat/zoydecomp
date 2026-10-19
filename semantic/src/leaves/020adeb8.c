/* arm9:020adeb8
 * True when the 64-bit field at p+0x2c is less than 0xe10 past the 32-bit now
 * stamp at q+0xc (unsigned 64-bit difference).
 */
int is_expired(void *p, void *q)
{
    unsigned long long deadline = *(unsigned long long *)((char *)p + 0x2c);
    unsigned int now = *(unsigned int *)((char *)q + 0xc);

    return (unsigned long long)(deadline - now) < 0xe10u;
}
