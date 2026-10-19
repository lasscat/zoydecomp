/* Clears the byte at offset 2 of the global structure at 0x021de53c. */
void clear_020ca95c(void)
{
    *(volatile unsigned char *)(0x021de53c + 2) = 0;
}
