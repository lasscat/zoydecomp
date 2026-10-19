/* arm9:0206e690 (12 bytes)
 * ldr r0, [r0, #0x658]
 * sub r0, r0, #1
 * bx lr
 *
 * Returns the 32-bit field at +0x658 minus one; the field is not
 * modified.
 */
unsigned int get_658_minus_one(void *this)
{
    return *(unsigned int *)((char *)this + 0x658) - 1;
}
