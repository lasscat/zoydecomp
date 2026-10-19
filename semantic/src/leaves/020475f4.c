/* arm9:020475f4 (12 bytes)
 *
 * Stores a fixed data pointer into the word at +0 of the object.
 *   ldr r1, [pc, #4]   ; r1 = 0x020e23cc
 *   str r1, [r0]       ; *(int *)self = 0x020e23cc
 *   bx  lr
 *
 * Unknown offset note: 0x020e23cc is an absolute data address (table/tag).
 */
void pvz_020475f4_set_ptr(int *self)
{
    *self = 0x020e23cc;
}
