/* arm9:0205a2b4 (12 bytes)
 * mov r1, #1
 * strb r1, [r0, #0x634]
 * bx lr
 *
 * Sets the 8-bit flag at offset 0x634 to 1.
 */
void pvz_0205a2b4_leaf(void *this) { *(unsigned char *)((char *)this + 0x634) = 1; }
