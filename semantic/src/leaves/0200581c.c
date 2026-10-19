/* arm9:0200581c
 * Store a 32-bit word into an indexed table at fixed base 0x02ff0dc4
 * (base word 0x02ff0000 + 0x0dc4), entries 4 bytes apart.
 * r0 = index, r1 = value.
 */
void store_word(unsigned int index, unsigned int value)
{
    *(volatile unsigned int *)(0x02FF0DC4u + index * 4u) = value;
}
