/* arm9:0200fb5c (12 bytes)
 *
 * Stores the single argument into the field at +8 of the fixed object based at
 * 0x020fffe0.
 *   ldr r1, [pc, #4]   ; r1 = 0x020fffe0
 *   str r0, [r1, #8]   ; *(int *)(0x020fffe0 + 8) = value
 *   bx  lr
 */
void pvz_0200fb5c_set(int value)
{
    *(int *)(0x020fffe0u + 8) = value;
}
