/* arm9:0205a2b4 (12 bytes)
 * mov r1, #1
 * strb r1, [r0, #0x634]
 * bx lr
 *
 * Sets the 8-bit flag at offset 0x634 to 1.
 */
void set_flag_634(void *this)
{
    *(unsigned char *)((char *)this + 0x634) = 1;
}
