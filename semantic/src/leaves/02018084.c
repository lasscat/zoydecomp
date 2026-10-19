/* arm9:02018084 (12 bytes)
 * ldr r1, [pc, #4]      ; r1 = 0x02100c20
 * strh r0, [r1, #8]     ; *(u16*)(0x02100c20 + 8) = value
 * bx lr
 *
 * Stores a 16-bit value into a fixed global at 0x02100c28.
 */
void store_word_02100c28(unsigned short value)
{
    *(volatile unsigned short *)0x02100C28u = value;
}
