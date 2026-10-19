/* arm9:0202f09c (20 bytes)
 *
 * Writes a byte into the object pointed to by *self, when that pointer is
 * non-NULL. The original re-loads *self for the store instead of keeping the
 * tested value in a register, so the pointer object is read twice.
 *   r2 = *self
 *   cmp r2, #0
 *   ldrne r0, [self]         ; reload the pointer
 *   strbne r1, [r0, #0x41]
 *   bx lr
 *
 * Unknown offset note: the pointee's +0x41 is a byte field.
 * The `volatile` on the pointer object only reproduces the original's two
 * independent reads of *self; the pointee is accessed as plain memory.
 */
void pvz_0202f09c_set_flag(char *volatile *self, char value)
{
    if (*self != 0)
        (*self)[0x41] = value;
}
