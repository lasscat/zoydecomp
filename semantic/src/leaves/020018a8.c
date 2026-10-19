/* arm9:020018a8 (28 bytes)
 * ldr r0, [pc, #0x14]  ; r0 = 0x04001008 (DISPCNT)
 * ldrh r0, [r0]
 * and r0, r0, #0x3c
 * asr r0, r0, #2
 * lsl r0, r0, #0xe
 * add r0, r0, #0x6200000
 * bx lr
 *
 * Returns 0x06200000 + ((DISPCNT & 0x3c) >> 2) << 14, i.e. a screen-base
 * offset derived from the display control register's mode field.
 */
unsigned int display_base(void)
{
    unsigned int v = *(volatile unsigned short *)0x04001008u;
    return 0x06200000u + ((v & 0x3Cu) >> 2 << 14);
}
