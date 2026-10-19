/*
 * arm9:02091aac  (20 bytes; byte-identical to arm9:0204907c)
 *
 * Original:
 *   mov  r1, #0
 *   str  r1, [r0]
 *   str  r1, [r0, #4]
 *   str  r1, [r0, #8]
 *   bx   lr
 *
 * Same three-word clear as 0x0204907c; the two addresses share one target hash,
 * so the same source is used. Record meaning is unknown.
 */
void pvz_02091aac_leaf(void *record)
{
    unsigned int *words = (unsigned int *)record;

    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
}
