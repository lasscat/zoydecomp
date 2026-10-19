/* arm9:020b8e80
 * If dst is non-null, copy the 12-byte default record at 0x02108db4 into it.
 * Returns bit 0 of the first word of that record.
 */
struct triple {
    unsigned int a;   /* +0x0 */
    unsigned int b;   /* +0x4 */
    unsigned int c;   /* +0x8 */
};

int load_default_triple(struct triple *dst)
{
    if (dst)
        *dst = *(struct triple *)0x02108DB4u;
    return (*(unsigned int *)0x02108DB4u & 1u) != 0;
}
