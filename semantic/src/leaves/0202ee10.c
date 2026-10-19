/* arm9:0202ee10
 * Stores value into the 32-bit slot of the global table at 0x02103C70;
 * slots are 0x24 bytes apart.  The table address comes from a literal pool.
 */
void set_table_slot(unsigned int index, unsigned int value)
{
    *(volatile unsigned int *)(0x02103C70u + index * 0x24u) = value;
}
