/*
 * arm9:02031b64  (12 bytes)
 *
 *   mov  r1, #0
 *   str  r1, [r0]
 *   bx   lr
 *
 * Clears the 32-bit word pointed to by the argument.
 */
void pvz_02031b64(unsigned int *target)
{
    *target = 0;
}
