/* arm9:020c10b0
 * Returns word `index` of the global table at 0x020DBF94.
 * The table address comes from a literal pool in the original.
 */
unsigned int get_table_word(unsigned int index)
{
    return *(volatile unsigned int *)(0x020DBF94u + index * 4u);
}
