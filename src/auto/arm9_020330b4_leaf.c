/* 020330b4 (arm9, 24 bytes)  -- EXACT byte match with clang23-arm946-o2
 *
 * Target:
 *   mov r1, #0
 *   str r1, [r0, #4]
 *   str r1, [r0]
 *   str r1, [r0, #0xc]
 *   str r1, [r0, #8]
 *   bx  lr
 *
 * Zero four consecutive 32-bit slots of p. The original stores in the order
 * #4, #0, #0xc, #8 (two pairs written high word first).
 *
 * NOTE: the pointer is declared volatile. Without volatile the optimizer
 * reorders the four stores into ascending address order (#0,#4,#8,#0xc);
 * volatile preserves the original non-ascending store order.
 * Slots at 0x0/0x4/0x8/0xc: unknown layout, cleared together.
 */
void pvz_020330b4_leaf(volatile unsigned int *p)
{
    p[1] = 0;
    p[0] = 0;
    p[3] = 0;
    p[2] = 0;
}
