/* arm9:020a7df4
 * Sets the byte flag at self+0x48 to 1.
 */
void pvz_020a7df4_leaf(unsigned char *self) { self[0x48] = 1; }
