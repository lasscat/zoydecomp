/* Returns the capability word at offset 0x200 when the byte flag at 0x88 is
   set; otherwise the word at 0x200 OR the word at 0xa0, masked by the
   complement of the word at 0xa4. The original if-converts all four loads;
   clang keeps the else path as a branch. */
unsigned int caps_020491d4(unsigned char *object)
{
    if (object[0x88])
        return *(unsigned int *)(object + 0x200);
    return ~*(unsigned int *)(object + 0xa4) &
           (*(unsigned int *)(object + 0x200) | *(unsigned int *)(object + 0xa0));
}
