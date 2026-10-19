/* arm9:02004dc8 (8 bytes)
 *
 * Word setter.
 *   str r1, [r0, #0xb4]  ; *(int *)(self + 0xb4) = value
 *   bx  lr
 *
 * Unknown offset note: +0xb4 is a 32-bit field of the object passed in r0.
 */
void pvz_02004dc8_leaf(char *self, int value) { *(int *)(self + 0xb4) = value; }
