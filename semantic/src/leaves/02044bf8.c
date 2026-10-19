/* Copies the word field at offset 8 of src into *dst. */
void copy_word8(void **dst, void *src)
{
    *dst = *(void **)((char *)src + 8);
}
