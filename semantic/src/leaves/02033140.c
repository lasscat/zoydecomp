/* arm9:02033140 h2 (24 bytes)
 * Signed variant: the target compares with the signed conditions
 * movge/movlt (cond 0xa/0xb), not the unsigned hs/lo used when the fields
 * are read as unsigned.
 */
int at_end(void *this)
{
    int a = *(int *)((char *)this + 0x08);
    int b = *(int *)((char *)this + 0x0c);
    return a >= b;
}
