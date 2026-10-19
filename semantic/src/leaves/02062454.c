/* Copy three 32-bit words from src into dst. */
void f(void *dst, void *src) {
    *(unsigned int *)((char *)dst + 0) = *(unsigned int *)((char *)src + 0);
    *(unsigned int *)((char *)dst + 4) = *(unsigned int *)((char *)src + 4);
    *(unsigned int *)((char *)dst + 8) = *(unsigned int *)((char *)src + 8);
}
