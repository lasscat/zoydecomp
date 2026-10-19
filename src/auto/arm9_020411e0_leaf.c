/* arm9:020411e0
 * Clear the word at p+0x14.
 */
void pvz_020411e0_leaf(void *p) { *(unsigned int *)((char *)p + 0x14) = 0; }
