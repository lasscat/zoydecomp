/*
 * arm9:02003f30  (40 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr   r3, [pc, #0x20]      ; r3 = 0x04000208 (IME)
 *   mov   r1, #0
 *   ldrh  r2, [r3]             ; saved = *IME
 *   strh  r1, [r3]             ; *IME = 0  (disable interrupts)
 *   ldr   r1, [r3, #8]         ; previous = *IE (0x04000210)
 *   str   r0, [r3, #8]         ; *IE = mask
 *   ldrh  r0, [r3]             ; re-read IME, result unused (hardware settle)
 *   mov   r0, r1               ; return previous IE value
 *   strh  r2, [r3]             ; *IME = saved
 *   bx    lr
 *
 * Replaces the interrupt-enable mask and returns the previous one, with IME
 * cleared while the mask is rewritten. The record at 0x04000208 is the DS
 * interrupt control block: IME at +0x00 (16-bit) and IE at +0x08 (32-bit).
 * The intermediate IME re-read has no value effect; the volatile qualifier
 * keeps it because the block is memory-mapped hardware.
 */

struct InterruptControl {
    volatile unsigned short ime;      /* +0x00  0x04000208 */
    unsigned short unknown_02[3];     /* +0x02 .. +0x07 */
    volatile unsigned int ie;         /* +0x08  0x04000210 */
};

unsigned int pvz_02003f30_leaf(unsigned int mask)
{
    volatile struct InterruptControl *control =
        (volatile struct InterruptControl *)0x04000208u;
    unsigned short saved_ime = control->ime;
    unsigned int previous;

    control->ime = 0;
    previous = control->ie;
    control->ie = mask;
    (void)control->ime;
    control->ime = saved_ime;
    return previous;
}
