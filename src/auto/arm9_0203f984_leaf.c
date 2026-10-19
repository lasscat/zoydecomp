/* arm9:0203f984
 * Return the 64-bit value at o+8 (low word in r0, high word in r1).
 */
long long pvz_0203f984_leaf(void *o)
{
    unsigned int lo = *(unsigned int *)((char *)o + 8);
    unsigned int hi = *(unsigned int *)((char *)o + 0xc);

    return (long long)lo | ((long long)hi << 32);
}
