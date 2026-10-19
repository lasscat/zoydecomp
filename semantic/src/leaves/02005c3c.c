/* arm9:02005c3c
 * Sets bit (1 << index) in the 16-bit control register at 0x020FD6E0.
 * The original narrows the shifted value back to 16 bits (lsl #16 / lsr #16)
 * before OR-ing it in; the address comes from a literal pool.
 */
void set_control_bit(unsigned int index)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x020FD6E0u;

    *reg = (unsigned short)(*reg | (1u << index));
}
