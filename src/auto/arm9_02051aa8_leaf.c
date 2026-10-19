/*
 * arm9:02051aa8  (12 bytes)
 *
 *   add  r1, r1, #4
 *   str  r1, [r0]
 *   bx   lr
 *
 * Stores the address of a node's +0x04 slot into the word pointed at by
 * the first argument (linking the caller to that slot).
 */
void pvz_02051aa8_leaf(unsigned int *out, unsigned int *node)
{
    *out = (unsigned int)((char *)node + 4);
}
