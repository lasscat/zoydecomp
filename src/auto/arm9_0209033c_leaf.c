/* 0209033c (12 bytes): clear a single word.
 *   mov r1, #0
 *   str r1, [r0]
 *   bx  lr
 * Stores 0 through the caller-supplied pointer. */
void pvz_0209033c_leaf(unsigned int *slot) { *slot = 0; }
