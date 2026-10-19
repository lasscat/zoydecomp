/* self+0x1c: packed word. If bit 24 is set, return low 24 bits of it;
   otherwise return the 32-bit value stored at self+8. */
unsigned int f(void *self) {
    unsigned int v = *(unsigned int *)((char *)self + 0x1c);
    if ((v >> 24) & 1u)
        return (v << 8) >> 8;
    return *(unsigned int *)((char *)self + 8);
}
