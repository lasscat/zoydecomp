/* arm9:0200f2cc (16 bytes)
 * ldr r0, [pc, #8]      ; r0 = 0x020ff6e0
 * ldr r0, [r0]          ; r0 = pointer held there
 * ldr r0, [r0, #0x1c]   ; return that object's word at +0x1c
 * bx lr
 *
 * Follows a global pointer and returns the 32-bit field at offset 0x1c
 * of the referenced object.
 */
unsigned int get_global_field_1c(void)
{
    unsigned int *object = *(unsigned int **)0x020FF6E0u;
    return *(unsigned int *)((char *)object + 0x1c);
}
