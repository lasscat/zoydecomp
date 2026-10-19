/* arm9:02067d8c (40 bytes)
 *
 * Exchanges a 16-bit value between two records and decrements a counter.
 *   r2 = *(int *)(other + 0x44)
 *   r3 = *(int *)(self + 0xc)
 *   r2 = r2 & 0xffff              ; lsl #0x10 / lsr #0x10
 *   *(int *)(self + 0xc) = r2
 *   *(int *)(other + 0x44) = r3
 *   (*(int *)(self + 0x10))--
 *   bx lr
 *
 * Unknown offset note: the fields at +0xc (self) and +0x44 (other) hold a value
 * whose low 16 bits are exchanged; +0x10 of self is a countdown.
 */
void pvz_02067d8c_swap(char *self, char *other)
{
    unsigned int take = *(unsigned int *)(other + 0x44) & 0xffffu;
    unsigned int give = *(unsigned int *)(self + 0xc);
    *(unsigned int *)(self + 0xc) = take;
    *(unsigned int *)(other + 0x44) = give;
    *(unsigned int *)(self + 0x10) -= 1;
}
