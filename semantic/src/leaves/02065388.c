/* arm9:02065388 (32 bytes)
 *
 * Adds delta to a 32-bit counter living inside a large object and clamps the
 * result to 0x2706.
 *   r0 = self + 0x5000
 *   r3 = *(int *)(r0 + 0xb00)       ; old counter
 *   r2 = 0x2706
 *   r1 = r3 + delta
 *   *(int *)(r0 + 0xb00) = r1
 *   if (r1 > r2) *(int *)(r0 + 0xb00) = r2
 *   bx lr
 *
 * Unknown offset note: 0x5000 + 0xb00 is the absolute offset of the counter
 * inside the object; 0x2706 is the clamp limit. The base is adjusted with a
 * separate add in the original, so the source keeps the two-part offset.
 */
void pvz_02065388_add_clamped(char *self, unsigned int delta)
{
    unsigned int *counter = (unsigned int *)(self + 0x5000 + 0xb00);
    unsigned int value = *counter + delta;
    *counter = value;
    if (value > 0x2706u)
        *counter = 0x2706u;
}
