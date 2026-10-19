/* Master-interrupt guard: disable IME, keep the previous IE value, merge in the
 * requested mask, then restore IME.  Returns the previous IE content.
 *   0x04000208 : IME (halfword)
 *   0x04000210 : IE  (word)
 */
unsigned int sub_02003f5c(unsigned int mask)
{
    volatile unsigned short *const ime = (volatile unsigned short *)0x04000208;
    volatile unsigned int *const ie = (volatile unsigned int *)0x04000210;

    unsigned short old_ime = *ime;
    *ime = 0;

    unsigned int old_ie = *ie;
    *ie = old_ie | mask;

    *ime = old_ime;
    return old_ie;
}
