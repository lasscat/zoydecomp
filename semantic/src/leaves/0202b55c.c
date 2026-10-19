/* Returns the word field at offset 0x78. */
unsigned get_field_78(int *p)
{
    return p[0x78 / 4];
}
