/*
 * arm9:0200e5c4  (8 bytes of code; the original's literal pool follows the code
 * and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r0, [pc]              ; r0 = 0x02fffa80
 *   bx   lr
 *
 * Returns the constant 0x02fffa80 (a fixed data address in the main-RAM mirror
 * at 0x02f00000, i.e. 0x023ffa80). What the returned pointer points at is
 * unknown.
 */
void *pvz_0200e5c4_leaf(void)
{
    return (void *)0x02fffa80u;
}
