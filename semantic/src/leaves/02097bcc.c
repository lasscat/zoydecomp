/* Adds the argument to the accumulator word at offset 0x5e8. */
void accumulate_02097bcc(unsigned char *object, unsigned int value)
{
    *(unsigned int *)(object + 0x5e8) += value;
}
