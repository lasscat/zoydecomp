/* arm9:02003af8
 * Returns the 16-bit counter at 0x020FD346 (word 0x020FD340 plus 6 bytes).
 * The original materialises the base 0x020FD340 from a literal pool, so the
 * target block carries no pool word of its own; clang folds base+6 into the
 * load and keeps the pool word inside .text.
 */
unsigned int get_counter(void)
{
    return *(volatile unsigned short *)0x020FD346u;
}
