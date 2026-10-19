/* arm9:020b8308 (8 bytes)
 * ldr r0, [r0, #8]
 * bx lr
 *
 * Returns the 32-bit word field at offset 8.
 */
unsigned int field_08(void *this)
{
    return *(unsigned int *)((char *)this + 0x08);
}
