/* Detaches the child held by the argument: clears the word at offset 0x154 of
   the child and then nulls the owning pointer. The original keeps the child in
   r2 and stores [child + 0x154] before [holder]; clang swaps both. */
void detach_02031b70(unsigned char *holder)
{
    unsigned char *child = *(unsigned char **)holder;
    if (child) {
        *(unsigned int *)(child + 0x154) = 0;
        *(unsigned int *)holder = 0;
    }
}
