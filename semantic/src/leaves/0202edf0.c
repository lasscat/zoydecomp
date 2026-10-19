/* Table of 0x24-byte records at 0x02103c6c; stores the zero extended halfword
   argument into the first word of the record selected by the index. */
void store_0202edf0(unsigned int index, unsigned short value)
{
    *(unsigned int *)(0x02103c6c + index * 0x24) = value;
}
