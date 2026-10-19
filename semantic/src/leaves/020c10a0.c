/* Returns entry 'index' of the word table at 0x020dd7fc. */
unsigned int entry_020c10a0(unsigned int index)
{
    return *(unsigned int *)(0x020dd7fc + index * 4);
}
