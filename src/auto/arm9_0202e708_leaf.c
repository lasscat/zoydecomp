/* arm9:0202e708 (20 bytes)
 *
 * Returns 1 when the 16-bit field at +0xc is zero, else 0.
 *   ldrh r0, [r0, #0xc]
 *   cmp  r0, #0
 *   moveq r0, #1
 *   movne r0, #0
 *   bx   lr
 *
 * Unknown offset note: +0xc is a 16-bit field of the object.
 */
int pvz_0202e708_leaf(char *self) { return *(unsigned short *)(self + 0xc) == 0; }
