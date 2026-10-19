/* Non-zero test of the word field at offset 0x88. The original materialises the
   boolean with cmp/movne/moveq; clang reuses the loaded value and returns it
   directly, so 16 instead of 20 bytes. */
int pvz_0209587c_leaf(unsigned char *object) { return *(unsigned int *)(object + 0x88) != 0; }
