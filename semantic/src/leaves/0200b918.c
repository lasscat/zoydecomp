/*
 * arm9:0200b918  (8 bytes)
 *
 *   mov  r0, #0
 *   bx   lr
 *
 * Constant getter that always reports "not present"/"no error".
 */
int pvz_0200b918(void)
{
    return 0;
}
