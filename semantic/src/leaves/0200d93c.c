/* arm9:0200d93c (20 bytes)
 *
 * Copies the global word at 0x02fffc3c into the field at +8 of the fixed object
 * based at 0x020ff5fc.
 *   ldr r1, [pc, #0xc]  ; r1 = 0x02fffc3c
 *   ldr r0, [pc, #0xc]  ; r0 = 0x020ff5fc
 *   ldr r1, [r1]        ; r1 = *(int *)0x02fffc3c   (source word)
 *   str r1, [r0, #8]    ; *(int *)(0x020ff5fc + 8) = r1
 *   bx  lr
 *
 * Unknown offset note: 0x020ff5fc is an object base, +8 is its 32-bit field.
 */
void pvz_0200d93c_copy(void)
{
    *(int *)(0x020ff5fcu + 8) = *(int *)0x02fffc3cu;
}
