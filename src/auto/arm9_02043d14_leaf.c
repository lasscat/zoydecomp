/* arm9:02043d14 (8 bytes)
 *
 * Constant predicate used as an "is supported" test.
 *   mov r0, #1
 *   bx  lr
 */
int pvz_02043d14_leaf(void) { return 1; }
