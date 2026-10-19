/* Stores the four supplied words into the four leading words of the record.
 * The fourth store is written through a volatile lvalue so this compiler does
 * not fold it into the store-multiple instruction of the first three; the
 * original keeps the stack argument load and the 0x0c store separate. */
void pvz_0204c000_store_four(unsigned int *record, unsigned int first,
                             unsigned int second, unsigned int third,
                             unsigned int fourth)
{
    record[0] = first;
    record[1] = second;
    record[2] = third;
    *(volatile unsigned int *)(record + 3) = fourth;
}
