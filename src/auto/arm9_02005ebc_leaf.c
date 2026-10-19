/* arm9:02005ebc (16 bytes) -- tier S
 *
 * Clears the word fields at +0 and +8. The stores are made volatile so that
 * this compiler keeps the original ascending order (the plain form emits +8
 * first and is only a 2-instruction near miss, kept as 02005ebc_h1.c).
 * The two fields are not memory-mapped; volatile here only fixes store order.
 *   mov r1, #0
 *   str r1, [r0]      ; +0x0 = 0
 *   str r1, [r0, #8]  ; +0x8 = 0
 *   bx  lr
 */
void pvz_02005ebc_leaf(char *self)
{
    *(volatile int *)(self + 0) = 0;
    *(volatile int *)(self + 8) = 0;
}
