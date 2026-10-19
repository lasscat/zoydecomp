/* Clear the byte flag at self+0x63. */
void pvz_0204b134_leaf(void *self) { *(unsigned char *)((char *)self + 0x63) = 0; }
