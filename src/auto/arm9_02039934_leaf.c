/* arm9:02039934 (8 bytes)
 * add r0, r0, #0x28
 * bx lr
 *
 * Returns a pointer 0x28 bytes past the argument.
 */
void *pvz_02039934_leaf(void *this) { return (char *)this + 0x28; }
