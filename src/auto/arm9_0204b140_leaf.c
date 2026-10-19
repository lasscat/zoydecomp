/* arm9:0204b140 (16 bytes)
 *
 * Increments the 32-bit counter at +0x24.
 *   r1 = *(int *)(self + 0x24)
 *   r1 = r1 + 1
 *   *(int *)(self + 0x24) = r1
 *   bx lr
 *
 * Unknown offset note: +0x24 is a 32-bit counter field.
 */
void pvz_0204b140_leaf(char *self) { *(int *)(self + 0x24) += 1; }
