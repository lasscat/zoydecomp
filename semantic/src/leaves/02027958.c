/* If offset is 0, return *self. Otherwise index into a table whose base is
   self+0xa (16-bit element) and add the caller offset, then read +4. */
unsigned int f(void *self, unsigned int offset) {
    if (offset == 0u)
        return *(unsigned int *)self;
    return *(unsigned int *)(offset + *(unsigned short *)((char *)self + 0xa) + 4);
}
