/* Push node onto the singly linked list at self+0x70; node+0x30 takes the
   previous head. */
void f(void *self, void *node) {
    *(void **)((char *)node + 0x30) = *(void **)((char *)self + 0x70);
    *(void **)((char *)self + 0x70) = node;
}
