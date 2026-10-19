/* Update one DISPCNT field and reset a "screen blanked" flag.
 * Globals (unknown layout, documented):
 *   0x020e04e0 : halfword blanked/selected flag, cleared when the new slot is 0
 *   0x020fd300 : halfword display slot that receives the new value
 *   0x04000000 : DISPCNT
 */
void sub_020012bc(unsigned short value, unsigned int bits, unsigned int shift)
{
    volatile unsigned short *const flag = (volatile unsigned short *)0x020e04e0;
    volatile unsigned short *const slot = (volatile unsigned short *)0x020fd300;
    volatile unsigned int *const disp = (volatile unsigned int *)0x04000000;

    unsigned short old = *flag;
    unsigned int current = *disp;

    *slot = value;

    unsigned int merged = (current & 0xfff0fff0u) | ((old != 0 ? (unsigned int)value : 0u) << 16);
    merged |= bits;
    merged |= shift << 3;

    *disp = merged;

    if (*slot == 0)
        *flag = 0;
}
