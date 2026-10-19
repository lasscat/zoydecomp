/* arm9:0207ad6c
 * Word at +0x28 of the 0x2c-byte record for index in the table at 0x020e680c.
 */
unsigned int record_field28(unsigned int index)
{
    return *(unsigned int *)(0x020E680Cu + index * 0x2cu + 0x28);
}
