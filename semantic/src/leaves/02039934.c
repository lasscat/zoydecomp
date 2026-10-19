/* arm9:02039934 (8 bytes)
 * add r0, r0, #0x28
 * bx lr
 *
 * Returns a pointer 0x28 bytes past the argument.
 */
void *offset_28(void *this)
{
    return (char *)this + 0x28;
}
