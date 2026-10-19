/* Clears the word at offset 4 of the global structure at 0x02106a98. */
void clear_02051b18(void)
{
    *(volatile unsigned int *)(0x02106a98 + 4) = 0;
}
