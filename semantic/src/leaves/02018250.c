/* Reports whether a byte field (offset 0x50d) of the object held by the word
   at 0x02100bf0+0xc equals one. */
int flag_is_one(void)
{
    unsigned char *obj = (unsigned char *)(*(unsigned *)(0x02100bf0u + 0xc));
    return obj[0x50d] == 1;
}
