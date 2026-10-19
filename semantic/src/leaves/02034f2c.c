/* arm9:02034f2c
 * Pointer to the 0x8c-byte record for index in the table at 0x02105d70.
 */
unsigned char *record_ptr(unsigned int index)
{
    return (unsigned char *)0x02105D70u + index * 0x8cu;
}
