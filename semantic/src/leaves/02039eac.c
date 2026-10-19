/* arm9:02039eac
 * Repack three signed words of p (+0, +4, +8) into a 16-bit value:
 * (p4>>3)<<5 | p0>>3 | (p8>>3)<<10, truncated to 16 bits.
 */
unsigned short repack_fields(void *p)
{
    int a = *(int *)((char *)p + 4);
    int x = *(int *)p;
    int b = *(int *)((char *)p + 8);

    return (unsigned short)(((a >> 3) << 5) | (x >> 3) | ((b >> 3) << 10));
}
