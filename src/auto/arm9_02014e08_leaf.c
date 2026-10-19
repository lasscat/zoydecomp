/* Returns the larger of the two unsigned arguments truncated to 16 bits
   (cmp/movls then lsl #16 / lsr #16 in the original). clang folds the
   truncation into an and with a materialised 0xffff, two bytes shorter. */
unsigned int pvz_02014e08_leaf(unsigned int a, unsigned int b)
{
    if (b <= a)
        b = a;
    return (unsigned short)b;
}
