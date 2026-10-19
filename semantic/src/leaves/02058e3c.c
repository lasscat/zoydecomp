/*
 * arm9:02058e3c  (40 bytes)
 *
 *   ldr   r3, [pc, #0x20]    ; literal 0x02107dd8 (flag byte at +1)
 *   ldrb  r0, [r3, #1]
 *   cmp   r0, #0
 *   ldrne ip, [pc, #0x18]    ; literal 0x02107ddc (table base)
 *   movne r0, #0x18          ; element size
 *   mlane r0, r1, r0, ip     ; base + index * 0x18
 *   movne r1, #0
 *   strne r1, [r0, r2, lsl #2]  ; zero one word of the element
 *   strbne r1, [r3, #1]         ; clear the pending flag
 *   bx    lr
 *
 * One-shot cleanup: when the "pending" byte at 0x02107dd9 is non-zero,
 * zeroes word `b` of the 0x18-byte table element `a` at 0x02107ddc and
 * clears the pending byte.
 */
void pvz_02058e3c(unsigned int a, unsigned int b)
{
    volatile unsigned char *flag = (volatile unsigned char *)0x02107dd8;

    if (flag[1] != 0) {
        unsigned int *element = (unsigned int *)(0x02107ddc + a * 0x18);

        element[b] = 0;
        flag[1] = 0;
    }
}
