/* Word field at offset 8 of the global table at 0x020fd640. */
unsigned int field_02005aa8(void)
{
    return *(volatile unsigned int *)(0x020fd640 + 8);
}
