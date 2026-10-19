/* Returns base + 16 * the halfword field at offset 8. */
unsigned pvz_0202ea44_leaf(unsigned *p) { return p[0] + (*(unsigned short *)((char *)p + 8) << 4); }
