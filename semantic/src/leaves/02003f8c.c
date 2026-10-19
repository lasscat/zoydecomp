/* Interrupt register helper.
 * 0x04000208 is the interrupt-enable halfword, 0x04000210 the request-flag word.
 * Saves IE, masks it off, clears the requested flag bits and restores IE.
 * The halfword register is re-read with the result unused; kept to preserve the
 * original access order (offset 8 name is not established, treated by address). */
void sub_02003f8c(unsigned int mask)
{
    volatile unsigned short *ie = (volatile unsigned short *)0x04000208u;

    unsigned short saved = *ie;

    *ie = 0;
    *(volatile unsigned int *)0x04000210u &= ~mask;
    (void)*ie;
    *ie = saved;
}
