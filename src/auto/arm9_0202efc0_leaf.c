/* arm9:0202efc0 (12 bytes)
 * mov r1, #0
 * str r1, [r0]
 * bx lr
 *
 * Clears the 32-bit word at offset 0.
 */
void pvz_0202efc0_leaf(void *this) { *(unsigned int *)this = 0; }
