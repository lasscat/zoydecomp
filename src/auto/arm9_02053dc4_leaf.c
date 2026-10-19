/* 02053dc4 (8 bytes): constant-returning accessor.
 *   mov r0, #0
 *   bx  lr
 * Always yields 0. */
int pvz_02053dc4_leaf(void) { return 0; }
