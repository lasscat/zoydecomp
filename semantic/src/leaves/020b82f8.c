/* Returns the word field at offset 0x0c. */
unsigned int get_c_020b82f8(unsigned char *object)
{
    return *(unsigned int *)(object + 0xc);
}
