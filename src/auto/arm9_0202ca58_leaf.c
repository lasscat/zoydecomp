/*
 * arm9:0202ca58  (8 bytes)
 *
 *   str  r1, [r0]
 *   bx   lr
 *
 * Plain 32-bit store of the second argument through the first.
 */
void pvz_0202ca58_leaf(unsigned int *target, unsigned int value) { *target = value; }
