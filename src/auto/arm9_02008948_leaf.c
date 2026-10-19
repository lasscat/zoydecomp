/* arm9:02008948 (8 bytes)
 * ldr r0, [r0, #0x38]
 * bx lr
 *
 * Returns the 32-bit word field at offset 0x38 of the object pointed to
 * by r0.
 */
unsigned int pvz_02008948_leaf(void *this) { return *(unsigned int *)((char *)this + 0x38); }
