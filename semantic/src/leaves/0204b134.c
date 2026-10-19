/* Clear the byte flag at self+0x63. */
void f(void *self) {
    *(unsigned char *)((char *)self + 0x63) = 0;
}
