/* Adds the argument to the accumulator word at offset 0x5e8. */
void pvz_02097bcc_leaf(unsigned char *object, unsigned int value)
{
    *(unsigned int *)(object + 0x5e8) += value;
}
